#include "TileRegistry.h"

Model::FTileRegistry::FTileRegistry()
{
    for (uint32_t i = 1; i <= 9; ++i)
    {
        Tiles.Emplace(1, i, ETileSide::V);
        Tiles.Emplace(1, i, ETileSide::R);
    }
    for (const FTile& Tile : Tiles)
    {
        TilePointers.Add(&Tile);
    }
}

const TArray<const Model::FTile*>& Model::FTileRegistry::GetTiles() const
{
    return TilePointers;
}

const Model::FTile* Model::FTileRegistry::GetTile(const FTileId& TileId) const
{
    return Tiles.FindByKey(TileId);
}
