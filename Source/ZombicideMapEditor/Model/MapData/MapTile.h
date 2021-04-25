#pragma once

namespace Model
{
    class FTile;

    class FMapTile : FNoncopyable
    {
    public:
        FMapTile(const FTile* const Tile, const uint32_t Rotation);

    private:
        const FTile* Tile;
        uint32_t Rotation;
    };
}
