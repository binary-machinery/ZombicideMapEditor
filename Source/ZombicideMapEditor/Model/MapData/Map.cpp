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
