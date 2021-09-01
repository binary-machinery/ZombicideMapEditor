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

Model::FTileId Model::FTileId::FromString(const FString& TileName)
{
    const ETileSide TileSide = TileName[TileName.Len() - 1] == 'V'
                               ? ETileSide::V
                               : ETileSide::R;
    const int32 CardId = FCString::Atoi(*TileName.LeftChop(1));
    return FTileId(CardId, TileSide);
}

Model::FTileId Model::FTileId::FromString(FString&& TileName)
{
    const ETileSide TileSide = TileName[TileName.Len() - 1] == 'V'
                                   ? ETileSide::V
                                   : ETileSide::R;
    TileName.LeftChopInline(1);
    const int32 CardId = FCString::Atoi(*TileName);
    return FTileId(CardId, TileSide);
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
