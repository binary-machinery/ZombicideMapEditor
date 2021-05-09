#include "TileId.h"

Model::FTileId::FTileId(const uint32 CardId, const ETileSide Side)
    : CardId(CardId),
      Side(Side)
{
}

Model::FTileId Model::FTileId::GetOtherSideTileId() const
{
    const ETileSide OtherSide = Side == ETileSide::V ? ETileSide::R : ETileSide::V;
    return FTileId(CardId, OtherSide);
}

FString Model::FTileId::ToString() const
{
    return FString::FromInt(CardId) + (Side == ETileSide::V ? TEXT("V") : TEXT("R"));
}
