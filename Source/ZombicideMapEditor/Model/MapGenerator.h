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

    private:
        static std::array<EMapTileRotation, 4> AvailableRotations;

        FMap* Map = nullptr;
        FTilePool* TilePool = nullptr;
    };
}
