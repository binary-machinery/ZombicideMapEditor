#pragma once
#include "TileId.h"

namespace Model
{
    class FTile
    {
    public:
        FTile(const FTileId& TileId, const FString& Set);

        const FString& GetSet() const
        {
            return Set;
        }

        const FTileId& GetTileId() const
        {
            return TileId;
        }

        friend bool operator==(const FTile& Tile, const FTileId& TileId)
        {
            return Tile.GetTileId() == TileId;
        }

        friend bool operator==(const FTile* const Tile, const FTileId& TileId)
        {
            return Tile->GetTileId() == TileId;
        }

    private:
        const FTileId TileId;
        const FString Set;
    };
}
