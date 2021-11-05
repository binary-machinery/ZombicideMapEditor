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

void AEditorModel::RegenerateMap()
{
    ResetMapTiles();
    MapGenerator->ResetIndices();
    GetWorldTimerManager().SetTimer(GenerateNextTileTimerHandle, this, &AEditorModel::GenerateNextTile,
                                    GenerateNextTileTimeInterval, true, GenerateNextTileTimeInterval);
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

void AEditorModel::ResetMapTiles()
{
    for (uint32 X = 0; X < Map->GetSizeX(); ++X)
    {
        for (uint32 Y = 0; Y < Map->GetSizeY(); ++Y)
        {
            ResetMapTile(X, Y);
        }
    }
}

AEditorModel::FMapUpdatedEvent& AEditorModel::OnMapUpdatedEvent()
{
    return MapUpdatedEvent;
}

void AEditorModel::Load()
{
    UE_LOG(LogTemp, Warning, TEXT("AEditorModel::Load"));

    CreateMap();

    Settings->OnMapSizeUpdated().AddLambda([this]()
    {
        ResetMapTiles();
        MapGenerator->ResetIndices();
        CreateMap();
    });
}

void AEditorModel::CreateMap()
{
    Map = MakeUnique<Model::FMap>(Settings->GetMapSizeX(), Settings->GetMapSizeY());
    MapGenerator->SetMap(Map.Get());

    GetWorldTimerManager().SetTimer(GenerateNextTileTimerHandle, this, &AEditorModel::GenerateNextTile,
                                    GenerateNextTileTimeInterval, true, GenerateNextTileTimeInterval);
}
