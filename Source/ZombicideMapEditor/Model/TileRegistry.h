#pragma once
#include "TileData/Tile.h"

namespace Model
{
    class FTileRegistry : FNoncopyable
    {
    public:
        FTileRegistry();
        const TArray<const FTile*>& GetTiles() const;
        const FTile* GetTile(const FTileId& TileId) const;

    private:
        TArray<FTile> Tiles;
        TArray<const FTile*> TilePointers;
    };
}
