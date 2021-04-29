#include "TileRegistry.h"

Model::FTileRegistry::FTileRegistry()
{
    Tiles.Emplace(1, 1, ETileSide::V);
    Tiles.Emplace(1, 2, ETileSide::R);
    Tiles.Emplace(1, 3, ETileSide::R);
    Tiles.Emplace(1, 4, ETileSide::V);
    Tiles.Emplace(1, 5, ETileSide::R);
    Tiles.Emplace(1, 6, ETileSide::R);
    Tiles.Emplace(1, 8, ETileSide::V);
    Tiles.Emplace(1, 9, ETileSide::R);
    Tiles.Emplace(1, 9, ETileSide::V);
    Tiles.Emplace(1, 10, ETileSide::R);
    Tiles.Emplace(1, 10, ETileSide::V);
    Tiles.Emplace(1, 11, ETileSide::R);
    Tiles.Emplace(1, 11, ETileSide::V);
    Tiles.Emplace(1, 12, ETileSide::R);
    Tiles.Emplace(1, 13, ETileSide::R);
    Tiles.Emplace(1, 14, ETileSide::R);
    Tiles.Emplace(1, 15, ETileSide::R);
    Tiles.Emplace(1, 16, ETileSide::R);
    Tiles.Emplace(1, 17, ETileSide::R);
    Tiles.Emplace(1, 18, ETileSide::R);
    Tiles.Emplace(1, 19, ETileSide::R);
    Tiles.Emplace(1, 20, ETileSide::R);
    Tiles.Emplace(1, 21, ETileSide::R);
    Tiles.Emplace(1, 22, ETileSide::R);
    Tiles.Emplace(1, 23, ETileSide::R);
    Tiles.Emplace(1, 24, ETileSide::R);

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
