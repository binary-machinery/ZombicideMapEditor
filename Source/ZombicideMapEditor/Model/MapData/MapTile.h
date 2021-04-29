#pragma once
#include "MapTileRotation.h"

namespace Model
{
    class FTile;

    class FMapTile
    {
    public:
        FMapTile(const FTile* const Tile, const EMapTileRotation Rotation);

        const FTile* GetTile() const
        {
            return Tile;
        }

        EMapTileRotation GetRotation() const
        {
            return Rotation;
        }

    private:
        const FTile* Tile;
        EMapTileRotation Rotation;
    };
}
