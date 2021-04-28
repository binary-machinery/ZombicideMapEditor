#pragma once
#include "MapTile.h"

namespace Model
{
    class FMap : FNoncopyable
    {
    public:
        FMap(const uint32 SizeX, const uint32 SizeY);
        void SetTile(const uint32 X, const uint32 Y, const FTile* const Tile, const EMapTileRotation Rotation);

        uint32 GetSizeX() const
        {
            return SizeX;
        }

        uint32 GetSizeY() const
        {
            return SizeY;
        }

    private:
        const uint32 SizeX;
        const uint32 SizeY;
        TArray<TArray<FMapTile>> TileGrid;
    };
}
