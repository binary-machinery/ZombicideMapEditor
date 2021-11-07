#include "TilePool.h"

#include "Settings.h"
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
    const uint32 Index = AvailableTiles.Find(Tile);
    AvailableTiles.RemoveAt(Index); // We modify the collection, TilePtr cannot be used anymore

    const Model::FTile** OtherSideTilePtr = AvailableTiles.FindByKey(TileId.GetOtherSideTileId());
    if (OtherSideTilePtr)
    {
        const Model::FTile* OtherSideTile = *OtherSideTilePtr; // Copy pointer before we modify AvailableTiles memory
        AvailableTiles.Remove(OtherSideTile); // We modify the collection, OtherSideTilePtr cannot be used anymore
        UnavailableTiles.Add(OtherSideTile);
        TileRemovedEvent.Broadcast(OtherSideTile->GetTileId());
    }

    TileRemovedEvent.Broadcast(TileId);
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
        TileAddedEvent.Broadcast(OtherSideTile->GetTileId());
    }

    SortAvailableTiles();
    TileAddedEvent.Broadcast(Tile->GetTileId());
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

void ATilePool::Load()
{
    UE_LOG(LogTemp, Warning, TEXT("ATilePool::Load"));

    LoadEnabledSetsToPool();

    Settings->OnSetToggledEvent().AddLambda([this](const FString& Set, const bool bIsEnabled)
    {
        LoadEnabledSetsToPool();
    });
}

void ATilePool::SortAvailableTiles()
{
    AvailableTiles.Sort([](const Model::FTile& Tile1, const Model::FTile& Tile2)
    {
        return Tile1.GetTileId() < Tile2.GetTileId();
    });
}

void ATilePool::LoadEnabledSetsToPool()
{
    AvailableTiles.Empty();
    UnavailableTiles.Empty();
    for (const Model::FTile* const Tile : TileRegistry->GetTiles())
    {
        if (Settings->IsSetEnabled(Tile->GetSet()))
        {
            AvailableTiles.Add(Tile);
        }
    }

    SortAvailableTiles();
    PoolRebuiltEvent.Broadcast();
}
