#pragma once
#include "TileSide.h"

namespace Model
{
    class FTileId
    {
    public:
        FTileId();
        FTileId(const uint32 CardId, const ETileSide Side);

        static FTileId FromString(const FString& TileName);
        static FTileId FromString(FString&& TileName);

        uint32 GetCardId() const;
        ETileSide GetSide() const;
        FTileId GetOtherSideTileId() const;
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
        uint32 CardId;
        ETileSide Side;
    };
}
