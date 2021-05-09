#include "TileId.h"

Model::FTileId::FTileId()
    : CardId(-1),
      Side(ETileSide::V)
{
}

Model::FTileId::FTileId(const uint32 CardId, const ETileSide Side)
    : CardId(CardId),
      Side(Side)
{
}

uint32 Model::FTileId::GetCardId() const
{
    return CardId;
}

Model::ETileSide Model::FTileId::GetSide() const
{
    return Side;
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
