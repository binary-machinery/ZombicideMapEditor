#pragma once
#include "TileSide.h"

namespace Model
{
    class FTileId
    {
    public:
        FTileId(const uint32 CardId, const ETileSide Side);
        FTileId GetOtherSideTileId() const;

        uint32 GetCardId() const
        {
            return CardId;
        }

        ETileSide GetSide() const
        {
            return Side;
        }

        FString ToString() const;

        friend bool operator==(const FTileId& Lhs, const FTileId& Rhs)
        {
            return Lhs.CardId == Rhs.CardId
                && Lhs.Side == Rhs.Side;
        }

        friend bool operator<(const FTileId& Lhs, const FTileId& Rhs)
        {
            if (Lhs.CardId != Rhs.CardId)
            {
                return Lhs.CardId < Rhs.CardId;
            }
            return Lhs.Side < Rhs.Side;
        }

        friend uint32 GetTypeHash(const FTileId& TileId)
        {
            return HashCombine(TileId.CardId, static_cast<uint32>(TileId.Side));
        }

    private:
        const uint32 CardId;
        const ETileSide Side;
    };
}
