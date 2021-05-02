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
    const FTile** TilePtr = AvailableTiles.FindByKey(TileId);
    if (!TilePtr)
    {
        return nullptr;
    }

    const FTile* Tile = *TilePtr; // Copy pointer before we modify AvailableTiles memory
    AvailableTiles.Remove(Tile); // We modify the collection, TilePtr cannot be used anymore

    const FTile** OtherSideTilePtr = AvailableTiles.FindByKey(TileId.GetOtherSideTileId());
    if (OtherSideTilePtr)
    {
        const FTile* OtherSideTile = *OtherSideTilePtr; // Copy pointer before we modify AvailableTiles memory
        AvailableTiles.Remove(OtherSideTile); // We modify the collection, OtherSideTilePtr cannot be used anymore
        UnavailableTiles.Add(OtherSideTile);
    }
    return Tile;
}

const Model::FTile* Model::FTilePool::TakeRandomTileFromPool()
{
    const uint32 Index = FMath::RandHelper(AvailableTiles.Num());
    return TakeTileFromPool(AvailableTiles[Index]->GetTileId());
}

void Model::FTilePool::ReturnTileToPool(const FTile* Tile)
{
    if (AvailableTiles.Find(Tile))
    {
        return;
    }

    AvailableTiles.Add(Tile);
    const FTileId OtherSideTileId = Tile->GetTileId().GetOtherSideTileId();
    const FTile** OtherSideTilePtr = UnavailableTiles.FindByKey(OtherSideTileId);
    if (OtherSideTilePtr)
    {
        const FTile* OtherSideTile = *OtherSideTilePtr; // Copy pointer before we modify UnavailableTiles memory
        UnavailableTiles.Remove(OtherSideTile); // We modify the collection, OtherSideTilePtr cannot be used anymore
        AvailableTiles.Add(OtherSideTile);
    }
}
