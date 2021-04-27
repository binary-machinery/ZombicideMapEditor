#include "MapGenerator.h"

#include "MapData/Map.h"

std::array<Model::EMapTileRotation, 4> Model::FMapGenerator::AvailableRotations = {
    EMapTileRotation::Rotation0,
    EMapTileRotation::Rotation90,
    EMapTileRotation::Rotation180,
    EMapTileRotation::Rotation270
};

void Model::FMapGenerator::SetMap(FMap* Value)
{
    this->Map = Value;
}

void Model::FMapGenerator::SetTilePool(FTilePool* Value)
{
    this->TilePool = Value;
}

void Model::FMapGenerator::Generate()
{
    checkf(Map, TEXT("Map is null"));
    checkf(TilePool, TEXT("TilePool is null"));

    for (uint32_t X = 0; X < Map->GetSizeX(); ++X)
    {
        for (uint32_t Y = 0; Y < Map->GetSizeY(); ++Y)
        {
            Map->SetTile(
                X, Y,
                TilePool->TakeRandomTileFromPool(),
                AvailableRotations[FMath::RandHelper(AvailableRotations.size())]
            );
        }
    }
}
