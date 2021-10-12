#include "EditorModel.h"

#include "MapGenerator.h"
#include "Settings.h"
#include "TilePool.h"
#include "TileData/Tile.h"

const Model::FMap& AEditorModel::GetMap() const
{
    return *Map;
}

void AEditorModel::GenerateNextTile()
{
    const bool bFinished = MapGenerator->GenerateNextTile();
    MapUpdatedEvent.Broadcast();

    if (bFinished)
    {
        GetWorldTimerManager().ClearTimer(GenerateNextTileTimerHandle);
    }
}

void AEditorModel::SetMapTile(const uint32 X, const uint32 Y, const Model::FTileId& TileId,
                              const Model::EMapTileRotation Rotation)
{
    const Model::FMapTile& CurrentMapTile = Map->GetMapTile(X, Y);
    if (CurrentMapTile.GetTile())
    {
        TilePool->ReturnTileToPool(CurrentMapTile.GetTile());
    }

    Map->SetTile(
        X, Y,
        TilePool->TakeTileFromPool(TileId),
        Rotation
    );
    MapUpdatedEvent.Broadcast();
}

void AEditorModel::ResetMapTile(const uint32 X, const uint32 Y)
{
    const Model::FMapTile& CurrentMapTile = Map->GetMapTile(X, Y);
    if (CurrentMapTile.GetTile())
    {
        TilePool->ReturnTileToPool(CurrentMapTile.GetTile());
        Map->ResetTile(X, Y);
        MapUpdatedEvent.Broadcast();
    }
}

AEditorModel::FMapUpdatedEvent& AEditorModel::OnMapUpdatedEvent()
{
    return MapUpdatedEvent;
}

void AEditorModel::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    UE_LOG(LogTemp, Warning, TEXT("AEditorModel::PostInitializeComponents"));
}

void AEditorModel::Load()
{
    UE_LOG(LogTemp, Warning, TEXT("AEditorModel::Load"));

    Map = MakeUnique<Model::FMap>(Settings->GetMapSizeX(), Settings->GetMapSizeY());
    MapGenerator->SetMap(Map.Get());

    GetWorldTimerManager().SetTimer(GenerateNextTileTimerHandle, this, &AEditorModel::GenerateNextTile,
                                    GenerateNextTileTimeInterval, true, GenerateNextTileTimeInterval);
}

void AEditorModel::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("AEditorModel::BeginPlay"));
}
