#pragma once

#include "TilePool.h"

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
        FMap* Map = nullptr;
        FTilePool* TilePool = nullptr;
    };
}
