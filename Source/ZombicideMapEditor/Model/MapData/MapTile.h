﻿#pragma once
#include "MapTileRotation.h"

namespace Model
{
    class FTile;

    class FMapTile
    {
    public:
        FMapTile(const FTile* const Tile, const EMapTileRotation Rotation);

    private:
        const FTile* Tile;
        EMapTileRotation Rotation;
    };
}
