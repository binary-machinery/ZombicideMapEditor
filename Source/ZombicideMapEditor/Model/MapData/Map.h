#pragma once
#include "MapTile.h"

namespace Model
{
    class FMap : FNoncopyable
    {
    public:
        FMap(const uint32 SizeX, const uint32 SizeY);
        void SetTile(const uint32 X, const uint32 Y, const FTile* const Tile, const EMapTileRotation Rotation);
        void ResetTile(const uint32 X, const uint32 Y);

        uint32 GetSizeX() const
        {
            return SizeX;
        }

        uint32 GetSizeY() const
        {
            return SizeY;
        }

        const FMapTile& GetMapTile(const uint32 X, const uint32 Y) const
        {
            return TileGrid[X][Y];
        }

    private:
        const uint32 SizeX;
        const uint32 SizeY;
        TArray<TArray<FMapTile>> TileGrid;
    };
}
