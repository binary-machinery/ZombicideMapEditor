#include "Map.h"

Model::FMap::FMap(const uint32_t SizeX, const uint32_t SizeY)
    : SizeX(SizeX),
      SizeY(SizeY)
{
    TileGrid.Reserve(SizeX);
    for (auto& Column : TileGrid)
    {
        Column.Reserve(SizeY);
    }
}

void Model::FMap::SetTile(const uint32_t X, const uint32_t Y, const FTile* const Tile, const EMapTileRotation Rotation)
{
    TileGrid[X][Y] = FMapTile(Tile, Rotation);
}
