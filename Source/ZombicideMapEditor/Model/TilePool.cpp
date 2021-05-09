#include "TilePool.h"

#include "TileRegistry.h"

ATilePool::ATilePool()
{
}

const TArray<const Model::FTile*>& ATilePool::GetAvailableTiles() const
{
    return AvailableTiles;
}

const Model::FTile* ATilePool::TakeTileFromPool(const Model::FTileId& TileId)
{
    const Model::FTile** TilePtr = AvailableTiles.FindByKey(TileId);
    if (!TilePtr)
    {
        return nullptr;
    }

    const Model::FTile* Tile = *TilePtr; // Copy pointer before we modify AvailableTiles memory
    AvailableTiles.Remove(Tile); // We modify the collection, TilePtr cannot be used anymore

    const Model::FTile** OtherSideTilePtr = AvailableTiles.FindByKey(TileId.GetOtherSideTileId());
    if (OtherSideTilePtr)
    {
        const Model::FTile* OtherSideTile = *OtherSideTilePtr; // Copy pointer before we modify AvailableTiles memory
        AvailableTiles.Remove(OtherSideTile); // We modify the collection, OtherSideTilePtr cannot be used anymore
        UnavailableTiles.Add(OtherSideTile);
    }

    OnTileRemovedEvent().Broadcast(Tile->GetTileId());
    return Tile;
}

const Model::FTile* ATilePool::TakeRandomTileFromPool()
{
    const uint32 Index = FMath::RandHelper(AvailableTiles.Num());
    return TakeTileFromPool(AvailableTiles[Index]->GetTileId());
}

void ATilePool::ReturnTileToPool(const Model::FTile* Tile)
{
    if (AvailableTiles.Find(Tile) != INDEX_NONE)
    {
        return;
    }

    AvailableTiles.Add(Tile);
    const Model::FTileId OtherSideTileId = Tile->GetTileId().GetOtherSideTileId();
    const Model::FTile** OtherSideTilePtr = UnavailableTiles.FindByKey(OtherSideTileId);
    if (OtherSideTilePtr)
    {
        const Model::FTile* OtherSideTile = *OtherSideTilePtr; // Copy pointer before we modify UnavailableTiles memory
        UnavailableTiles.Remove(OtherSideTile); // We modify the collection, OtherSideTilePtr cannot be used anymore
        AvailableTiles.Add(OtherSideTile);
    }

    OnTileAddedEvent().Broadcast(Tile->GetTileId());
}

ATilePool::FPoolRebuiltEvent& ATilePool::OnPoolRebuiltEvent()
{
    return PoolRebuiltEvent;
}

ATilePool::FTileAddedEvent& ATilePool::OnTileAddedEvent()
{
    return TileAddedEvent;
}

ATilePool::FTileRemovedEvent& ATilePool::OnTileRemovedEvent()
{
    return TileRemovedEvent;
}

void ATilePool::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    UE_LOG(LogTemp, Warning, TEXT("ATilePool::PostInitializeComponents"));
}

void ATilePool::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("ATilePool::BeginPlay"));

    AvailableTiles.Empty();
    UnavailableTiles.Empty();
    for (const Model::FTile* const Tile : TileRegistry->GetTiles())
    {
        AvailableTiles.Add(Tile);
    }

    OnPoolRebuiltEvent().Broadcast();
}
