#pragma once

#include "TilePool.h"
#include "MapData/MapTileRotation.h"
#include <array>

namespace Model
{
    class FMap;
    class FTilePool;

    class FMapGenerator : FNoncopyable
    {
    public:
        void SetMap(FMap* Value);
        void SetTilePool(FTilePool* Value);
        void Generate();
        void GenerateNextTile();

    private:
        static std::array<EMapTileRotation, 4> AvailableRotations;

        FMap* Map = nullptr;
        FTilePool* TilePool = nullptr;

        uint32 CurrentX = 0;
        uint32 CurrentY = 0;
    };
}
