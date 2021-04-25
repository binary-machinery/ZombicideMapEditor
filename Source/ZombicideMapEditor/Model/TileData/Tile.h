#pragma once
#include "TileId.h"
#include "TileSide.h"

namespace Model
{
    class FTile
    {
    public:
        FTile(const uint32_t SetId, const uint32_t CardId, const ETileSide Side);

        uint32_t GetSetId() const
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
        const uint32_t SetId;
        const FTileId TileId;
    };
}
