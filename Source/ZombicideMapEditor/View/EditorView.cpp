#include "EditorView.h"

#include "GenerationWidget.h"
#include "PaperSprite.h"
#include "TileSpriteActor.h"
#include "UiWidget.h"
#include "TilePoolWidget.h"
#include "TilePoolItemWidget.h"
#include "SettingsWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ZombicideMapEditor/Model/EditorModel.h"
#include "ZombicideMapEditor/Model/TilePool.h"
#include "ZombicideMapEditor/Model/TileData/Tile.h"

AEditorView::AEditorView()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEditorView::Load()
{
    UE_LOG(LogTemp, Warning, TEXT("AEditorView::Load"));

    ModelActor->OnMapUpdatedEvent().AddLambda([this]() { RedrawMap(); }); // TODO: Redraw the changed sprite only

    TilePool->OnPoolRebuiltEvent().AddLambda([this]()
    {
        RebuildTilePoolItemWidgets();
        TilePoolWidget->SortTilePoolItemWidgets();
    });

    TilePool->OnTileAddedEvent().AddLambda([this](const Model::FTileId& TileId)
    {
        AddTilePoolItemWidget(TileId);
        TilePoolWidget->SortTilePoolItemWidgets();
    });

    TilePool->OnTileRemovedEvent().AddLambda([this](const Model::FTileId& TileId)
    {
        RemoveTilePoolItemWidget(TileId);
    });

    for (UPaperSprite* TileSprite : TileSprites)
    {
        TileSpritesMap.Add(Model::FTileId::FromString(TileSprite->GetName()), TileSprite);
    }

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    PlayerController->SetShowMouseCursor(true);
    PlayerController->InputComponent->BindAction("MouseLeftButtonClick", IE_Released, this,
                                                 &AEditorView::OnMouseLeftButtonClick);
    PlayerController->InputComponent->BindAction("MouseRightButtonClick", IE_Released, this,
                                                 &AEditorView::OnMouseRightButtonClick);

    UiWidget = CreateWidget<UUiWidget>(
        GetWorld(),
        UiWidgetType,
        FName(TEXT("Ui"))
    );
    UiWidget->AddToViewport();

    TilePoolWidget = CreateWidget<UTilePoolWidget>(
        GetWorld(),
        TilePoolWidgetType,
        FName(TEXT("TilePool"))
    );
    TilePoolWidget->OnTileSelectedEvent().AddLambda([this](const Model::FTileId& TileId)
    {
        OnSelectedTileChanged(TileId);
    });

    UiWidget->SetTilePoolWidget(TilePoolWidget);

    GenerationWidget = CreateWidget<UGenerationWidget>(
        GetWorld(),
        GenerationWidgetType,
        FName(TEXT("Generation"))
    );
    GenerationWidget->OnRegenerateMapEvent().AddLambda([this]()
    {
        ModelActor->RegenerateMap();
    });

    UiWidget->SetGenerationWidget(GenerationWidget);

    SettingsWidget = CreateWidget<USettingsWidget>(
        GetWorld(),
        SettingsWidgetType,
        FName(TEXT("Settings"))
    );

    UiWidget->SetSettingsWidget(SettingsWidget);
    SettingsWidget->SetSettings(Settings);

    RebuildTilePoolItemWidgets();
}

void AEditorView::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (SelectedTileSpriteActor != nullptr)
    {
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        FVector WorldPosition, WorldDirection;
        PlayerController->DeprojectMousePositionToWorld(WorldPosition, WorldDirection);

        // Snap to the grid
        const int32 IndexX = WorldXToGridIndexX(WorldPosition.X);
        const int32 IndexY = WorldZToGridIndexY(WorldPosition.Z);
        if (IndexX < 0 || static_cast<uint32>(IndexX) >= ModelActor->GetMap().GetSizeX()
            || IndexY < 0 || static_cast<uint32>(IndexY) >= ModelActor->GetMap().GetSizeY())
        {
            SelectedTileSpriteActor->SetActorHiddenInGame(true);
            return;
        }

        const float X = GridIndexXToWorldX(IndexX);
        const float Y = SelectedTileSpriteActor->GetActorLocation().Y;
        const float Z = GridIndexYToWorldZ(IndexY);

        SelectedTileSpriteActor->SetActorLocation(FVector(X, Y, Z));
        SelectedTileSpriteActor->SetActorHiddenInGame(false);
    }
}

void AEditorView::OnMouseLeftButtonClick()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    FVector WorldPosition, WorldDirection;
    PlayerController->DeprojectMousePositionToWorld(WorldPosition, WorldDirection);

    const uint32 IndexX = WorldXToGridIndexX(WorldPosition.X);
    const uint32 IndexY = WorldZToGridIndexY(WorldPosition.Z);
    if (IndexX < 0 || static_cast<uint32>(IndexX) >= ModelActor->GetMap().GetSizeX()
        || IndexY < 0 || static_cast<uint32>(IndexY) >= ModelActor->GetMap().GetSizeY())
    {
        return;
    }

    if (SelectedTileSpriteActor != nullptr)
    {
        ModelActor->SetMapTile(
            IndexX, IndexY,
            SelectedTileSpriteActor->GetTileId(),
            SelectedTileSpriteActor->GetRotation()
        );
        SelectedTileSpriteActor->Destroy();
        SelectedTileSpriteActor = nullptr;
    }
    else
    {
        const Model::FMapTile& MapTile = ModelActor->GetMap().GetMapTile(IndexX, IndexY);
        if (MapTile.GetTile())
        {
            const Model::FTileId& TileId = MapTile.GetTile()->GetTileId();
            const Model::EMapTileRotation Rotation = MapTile.GetRotation();
            ModelActor->ResetMapTile(IndexX, IndexY);
            SelectedTileSpriteActor = GetWorld()->SpawnActor<ATileSpriteActor>(
                SelectedTileActorType,
                FVector(0, 5, 0),
                FRotator::ZeroRotator
            );
            SelectedTileSpriteActor->SetTileData(TileId, TileSpritesMap[TileId]);
            SelectedTileSpriteActor->SetRotation(Rotation);
        }
    }
}

void AEditorView::OnMouseRightButtonClick()
{
    if (SelectedTileSpriteActor == nullptr)
    {
        return;
    }

    SelectedTileSpriteActor->Rotate();
}

void AEditorView::RedrawMap()
{
    for (ATileSpriteActor* TileSpriteActor : TileSpriteActors)
    {
        TileSpriteActor->Destroy();
    }
    TileSpriteActors.Empty();

    const Model::FMap& Map = ModelActor->GetMap();
    for (uint32 X = 0; X < Map.GetSizeX(); ++X)
    {
        for (uint32 Y = 0; Y < Map.GetSizeY(); ++Y)
        {
            const Model::FMapTile& MapTile = Map.GetMapTile(X, Y);
            if (MapTile.GetTile())
            {
                SpawnSprite(X, Y, MapTile.GetTile()->GetTileId(), MapTile.GetRotation());
            }
        }
    }
}

void AEditorView::SpawnSprite(const uint32 X, const uint32 Y, const Model::FTileId& TileId,
                              const Model::EMapTileRotation Rotation)
{
    ATileSpriteActor* TileSpriteActor = GetWorld()->SpawnActor<ATileSpriteActor>(MapTileActorType);
    TileSpriteActor->SetTileData(TileId, TileSpritesMap[TileId]);
    TileSpriteActor->SetPosition(GridIndexXToWorldX(X), GridIndexYToWorldZ(Y));
    TileSpriteActor->SetRotation(Rotation);
    TileSpriteActors.Add(TileSpriteActor);
}

void AEditorView::RebuildTilePoolItemWidgets()
{
    TilePoolWidget->ClearTilePoolItemWidgets();
    for (const Model::FTile* Tile : TilePool->GetAvailableTiles())
    {
        UTilePoolItemWidget* TilePoolItemWidget = CreateWidget<UTilePoolItemWidget>(
            TilePoolWidget,
            TilePoolItemWidgetType
        );
        TilePoolWidget->AddTilePoolItemWidget(TilePoolItemWidget);

        UPaperSprite* PaperSprite = TileSpritesMap[Tile->GetTileId()];
        TilePoolItemWidget->SetTileId(Tile->GetTileId());
        TilePoolItemWidget->SetTileTexture(PaperSprite->GetSourceTexture());
    }
}

void AEditorView::AddTilePoolItemWidget(const Model::FTileId& TileId)
{
    UTilePoolItemWidget* TilePoolItemWidget = CreateWidget<UTilePoolItemWidget>(
        TilePoolWidget,
        TilePoolItemWidgetType
    );
    TilePoolWidget->AddTilePoolItemWidget(TilePoolItemWidget);

    UPaperSprite* PaperSprite = TileSpritesMap[TileId];
    TilePoolItemWidget->SetTileId(TileId);
    TilePoolItemWidget->SetTileTexture(PaperSprite->GetSourceTexture());
}

void AEditorView::RemoveTilePoolItemWidget(const Model::FTileId& TileId)
{
    TilePoolWidget->RemoveTilePoolItemWidget(TileId);
}

void AEditorView::OnSelectedTileChanged(const Model::FTileId& TileId)
{
    UE_LOG(LogTemp, Warning, TEXT("AEditorView::OnSelectedTileChanged"));
    if (SelectedTileSpriteActor == nullptr)
    {
        SelectedTileSpriteActor = GetWorld()->SpawnActor<ATileSpriteActor>(
            SelectedTileActorType,
            FVector(0, 5, 0),
            FRotator::ZeroRotator
        );
    }
    SelectedTileSpriteActor->SetTileData(TileId, TileSpritesMap[TileId]);
}

float AEditorView::GetAdjustedMapOffsetX() const
{
    return MapOffsetX - MapTileSize * ModelActor->GetMap().GetSizeX() / 2.0f;
}

float AEditorView::GetAdjustedOffsetY() const
{
    return MapOffsetY - MapTileSize * ModelActor->GetMap().GetSizeY() / 2.0f;
}

int32 AEditorView::WorldXToGridIndexX(const float WorldX)
{
    return FMath::FloorToInt((WorldX - GetAdjustedMapOffsetX() + MapTileSize / 2) / MapTileSize);
}

int32 AEditorView::WorldZToGridIndexY(const float WorldZ)
{
    return FMath::FloorToInt((WorldZ - GetAdjustedOffsetY() + MapTileSize / 2) / MapTileSize);
}

float AEditorView::GridIndexXToWorldX(const int32 GridIndexX)
{
    return GridIndexX * MapTileSize + GetAdjustedMapOffsetX();
}

float AEditorView::GridIndexYToWorldZ(const int32 GridIndexY)
{
    return GridIndexY * MapTileSize + GetAdjustedOffsetY();
}
