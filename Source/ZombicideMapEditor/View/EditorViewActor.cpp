#include "EditorViewActor.h"

#include "PaperSprite.h"
#include "TileSpriteActor.h"
#include "ZombicideMapEditor/Model/EditorModelActor.h"
#include "ZombicideMapEditor/Model/TileData/Tile.h"

// Sets default values
AEditorViewActor::AEditorViewActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEditorViewActor::BeginPlay()
{
    Super::BeginPlay();

    ModelActor->OnGeneratedMapEvent().AddLambda([this]() { RedrawMap(); });
    ModelActor->OnGeneratedNextTileEvent().AddLambda([this]() { RedrawMap(); }); // TODO: Redraw the changed sprite only

    for (UPaperSprite* TileSprite : TileSprites)
    {
        FString TileName = TileSprite->GetName();
        const Model::ETileSide TileSide = TileName[TileName.Len() - 1] == 'V'
                                              ? Model::ETileSide::V
                                              : Model::ETileSide::R;
        TileName.LeftChopInline(1);
        const int32 CardId = FCString::Atoi(*TileName);
        TileSpritesMap.Add(Model::FTileId(CardId, TileSide), TileSprite);
    }
}

// Called every frame
void AEditorViewActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEditorViewActor::RedrawMap()
{
    for (ATileSpriteActor* TileSpriteActor : TileSpriteActors)
    {
        TileSpriteActor->Destroy();
    }
    TileSpriteActors.Empty();

    const Model::FMap& Map = ModelActor->GetMap();
    for (uint32 X = 0; X < Map.GetSizeX(); ++X)
    {
        for (uint32 Y = 0; Y < Map.GetSizeX(); ++Y)
        {
            const Model::FMapTile& MapTile = Map.GetMapTile(X, Y);
            if (MapTile.GetTile())
            {
                SpawnSprite(X, Y, MapTile.GetTile()->GetTileId(), MapTile.GetRotation());
            }
        }
    }
}

void AEditorViewActor::SpawnSprite(const uint32 X, const uint32 Y, const Model::FTileId& TileId,
                                   const Model::EMapTileRotation Rotation)
{
    const float OffsetX = 250;
    const float OffsetY = 125;
    ATileSpriteActor* TileSpriteActor = GetWorld()->SpawnActor<ATileSpriteActor>(
        ATileSpriteActor::StaticClass(),
        FVector(X * 250 - OffsetX, 0, Y * 250 - OffsetY),
        FRotator::MakeFromEuler(FVector(0, static_cast<float>(Rotation), 0))
    );
    TileSpriteActor->SetSprite(TileSpritesMap[TileId]);
    TileSpriteActors.Add(TileSpriteActor);
}
