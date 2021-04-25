#pragma once
#include "Tile.h"

namespace Model
{
    class FMap : FNoncopyable
    {
    public:
        FMap(const uint32_t SizeX, const uint32_t SizeY)
            : SizeX(SizeX),
              SizeY(SizeY)
        {
            TileGrid.Reserve(SizeX);
            for (TArray<const FTile*>& Column : TileGrid)
            {
                Column.Reserve(SizeY);
            }
        }

        uint32_t GetSizeX() const
        {
            return SizeX;
        }

        uint32_t GetSizeY() const
        {
            return SizeY;
        }

    private:
        uint32_t SizeX;
        uint32_t SizeY;
        TArray<TArray<const FTile*>> TileGrid;
    };
}
