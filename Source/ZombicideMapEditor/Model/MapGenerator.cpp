#include "MapGenerator.h"

#include "TilePool.h"
#include "MapData/Map.h"

std::array<Model::EMapTileRotation, 4> AMapGenerator::AvailableRotations = {
    Model::EMapTileRotation::Rotation0,
    Model::EMapTileRotation::Rotation90,
    Model::EMapTileRotation::Rotation180,
    Model::EMapTileRotation::Rotation270
};

void AMapGenerator::SetMap(Model::FMap* Value)
{
    this->Map = Value;
}

void AMapGenerator::ResetIndices()
{
    CurrentX = 0;
    CurrentY = 0;
}

bool AMapGenerator::GenerateNextTile()
{
    const Model::FMapTile& CurrentMapTile = Map->GetMapTile(CurrentX, CurrentY);
    if (CurrentMapTile.GetTile())
    {
        TilePool->ReturnTileToPool(CurrentMapTile.GetTile());
    }

    const Model::FTile* Tile = TilePool->TakeRandomTileFromPool();
    if (!Tile)
    {
        ResetIndices();
        return true;
    }

    Map->SetTile(CurrentX, CurrentY, Tile, AvailableRotations[FMath::RandHelper(AvailableRotations.size())]);

    ++CurrentX;
    if (CurrentX >= Map->GetSizeX())
    {
        CurrentX = 0;
        ++CurrentY;
        if (CurrentY >= Map->GetSizeY())
        {
            CurrentY = 0;
            return true;
        }
    }
    return false;
}

void AMapGenerator::Load()
{
    UE_LOG(LogTemp, Warning, TEXT("AMapGenerator::Load"));
}
