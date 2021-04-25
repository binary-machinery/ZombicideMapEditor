#pragma once

namespace Model
{
    class FTileId;
    class FTile;

    class FTilePool : FNoncopyable
    {
    public:
        const TArray<const FTile*>& GetAvailableTiles() const;
        const FTile* TakeTileFromPool(const FTileId& TileId);
        void ReturnTileToPool(const FTile* Tile);

    private:
        TArray<const FTile*> AvailableTiles;
        TArray<const FTile*> UnavailableTiles;
    };
}
