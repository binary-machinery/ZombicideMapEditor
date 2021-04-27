#include "Map.h"

Model::FMap::FMap(const uint32_t SizeX, const uint32_t SizeY)
    : SizeX(SizeX),
      SizeY(SizeY)
{
    TileGrid.Reserve(SizeX);
    for (uint32_t X = 0; X < SizeX; ++X)
    {
        TileGrid.Emplace();
        auto& Column = TileGrid[X];
        Column.Reserve(SizeY);
        for (uint32_t Y = 0; Y < SizeY; ++Y)
        {
            Column.Emplace(nullptr, EMapTileRotation::Rotation0);
        }
    }
}

void Model::FMap::SetTile(const uint32_t X, const uint32_t Y, const FTile* const Tile, const EMapTileRotation Rotation)
{
    TileGrid[X][Y] = FMapTile(Tile, Rotation);
}
