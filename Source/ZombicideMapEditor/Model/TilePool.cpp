#include "TilePool.h"
#include "TileData/Tile.h"
#include "TileRegistry.h"

void Model::FTilePool::Init(const FTileRegistry& TileRegistry)
{
    AvailableTiles.Empty();
    UnavailableTiles.Empty();
    for (const FTile* const Tile : TileRegistry.GetTiles())
    {
        AvailableTiles.Add(Tile);
    }
}

const TArray<const Model::FTile*>& Model::FTilePool::GetAvailableTiles() const
{
    return AvailableTiles;
}

const Model::FTile* Model::FTilePool::TakeTileFromPool(const FTileId& TileId)
{
    const FTile** Tile = AvailableTiles.FindByKey(TileId);
    if (Tile)
    {
        AvailableTiles.Remove(*Tile);
        const FTile** OtherSideTile = AvailableTiles.FindByKey(TileId.GetOtherSideTileId());
        if (OtherSideTile)
        {
            AvailableTiles.Remove(*OtherSideTile);
            UnavailableTiles.Add(*OtherSideTile);
        }
    }
    return *Tile;
}

void Model::FTilePool::ReturnTileToPool(const FTile* Tile)
{
    if (AvailableTiles.Find(Tile))
    {
        return;
    }

    AvailableTiles.Add(Tile);
    const FTile** OtherSideTile = UnavailableTiles.FindByKey(Tile->GetTileId().GetOtherSideTileId());
    if (OtherSideTile)
    {
        UnavailableTiles.Remove(*OtherSideTile);
        AvailableTiles.Add(*OtherSideTile);
    }
}
