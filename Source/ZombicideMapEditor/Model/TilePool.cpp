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
    if (TilePtr)
    {
        AvailableTiles.RemoveAll([&TileId](const FTile* Tile) { return Tile->GetTileId() == TileId; });
        const FTileId OtherSideTileId = TileId.GetOtherSideTileId();
        const FTile** OtherSideTilePtr = AvailableTiles.FindByKey(OtherSideTileId);
        if (OtherSideTilePtr)
        {
            AvailableTiles.RemoveAll([&OtherSideTileId](const FTile* Tile)
            {
                return Tile->GetTileId() == OtherSideTileId;
            });
            UnavailableTiles.Add(*OtherSideTilePtr);
        }
    }
    return *TilePtr;
}

const Model::FTile* Model::FTilePool::TakeRandomTileFromPool()
{
    const uint32_t Index = FMath::RandHelper(AvailableTiles.Num());
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
        UnavailableTiles.RemoveAll([&OtherSideTileId](const FTile* Tile)
        {
            return Tile->GetTileId() == OtherSideTileId;
        });
        AvailableTiles.Add(*OtherSideTilePtr);
    }
}
