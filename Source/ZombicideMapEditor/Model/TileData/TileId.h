#pragma once
#include "TileSide.h"

namespace Model
{
    class FTileId
    {
    public:
        FTileId(const uint32_t CardId, const ETileSide Side);
        FTileId GetOtherSideTileId() const;

        friend bool operator==(const FTileId& Lhs, const FTileId& Rhs)
        {
            return Lhs.CardId == Rhs.CardId
                && Lhs.Side == Rhs.Side;
        }

    private:
        const uint32_t CardId;
        const ETileSide Side;
    };
}
