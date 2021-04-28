#pragma once
#include "TileId.h"
#include "TileSide.h"

namespace Model
{
    class FTile
    {
    public:
        FTile(const uint32 SetId, const uint32 CardId, const ETileSide Side);

        uint32 GetSetId() const
        {
            return SetId;
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
        const uint32 SetId;
        const FTileId TileId;
    };
}
