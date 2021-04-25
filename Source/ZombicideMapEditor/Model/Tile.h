#pragma once

namespace Model
{
    class FTile : FNoncopyable
    {
    public:
        enum class ESide
        {
            V = 0,
            R = 1,
        };

        FTile(const uint32_t SetId, const uint32_t TileId, const ESide TileSide)
            : SetId(SetId),
              TileId(TileId),
              TileSide(TileSide)
        {
        }

        uint32_t GetSetId() const
        {
            return SetId;
        }

        uint32_t GetTileId() const
        {
            return TileId;
        }

        ESide GetTileSide() const
        {
            return TileSide;
        }

    private:
        uint32_t SetId;
        uint32_t TileId;
        ESide TileSide;
    };
}
