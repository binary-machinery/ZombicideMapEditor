#pragma once
#include "MapTile.h"

namespace Model
{
    class FMap : FNoncopyable
    {
    public:
        FMap(const uint32_t SizeX, const uint32_t SizeY);

        uint32_t GetSizeX() const
        {
            return SizeX;
        }

        uint32_t GetSizeY() const
        {
            return SizeY;
        }

    private:
        const uint32_t SizeX;
        const uint32_t SizeY;
        TArray<TArray<const FMapTile*>> TileGrid;
    };
}
