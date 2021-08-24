#include "Map.h"

Model::FMap::FMap(const uint32 SizeX, const uint32 SizeY)
    : SizeX(SizeX),
      SizeY(SizeY)
{
    TileGrid.Reserve(SizeX);
    for (uint32 X = 0; X < SizeX; ++X)
    {
        TileGrid.Emplace();
        auto& Column = TileGrid[X];
        Column.Reserve(SizeY);
        for (uint32 Y = 0; Y < SizeY; ++Y)
        {
            Column.Emplace(nullptr, EMapTileRotation::Rotation0);
        }
    }
}

void Model::FMap::SetTile(const uint32 X, const uint32 Y, const FTile* const Tile, const EMapTileRotation Rotation)
{
    TileGrid[X][Y] = FMapTile(Tile, Rotation);
}

void Model::FMap::ResetTile(const uint32 X, const uint32 Y)
{
    TileGrid[X][Y] = FMapTile(nullptr, EMapTileRotation::Rotation0);
}
