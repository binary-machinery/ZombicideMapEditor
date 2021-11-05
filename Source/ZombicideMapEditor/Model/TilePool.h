#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombicideMapEditor/ILoadable.h"
#include "TilePool.generated.h"

class ATileRegistry;

namespace Model
{
    class FTileId;
    class FTile;
}

UCLASS()
class ZOMBICIDEMAPEDITOR_API ATilePool : public AActor, public ILoadable
{
    GENERATED_BODY()

public:
    DECLARE_EVENT(ATilePool, FPoolRebuiltEvent)

    DECLARE_EVENT_OneParam(ATilePool, FTileAddedEvent, const Model::FTileId&)

    DECLARE_EVENT_OneParam(ATilePool, FTileRemovedEvent, const Model::FTileId&)

    ATilePool();
    const TArray<const Model::FTile*>& GetAvailableTiles() const;
    const Model::FTile* TakeTileFromPool(const Model::FTileId& TileId);
    const Model::FTile* TakeRandomTileFromPool();
    void ReturnTileToPool(const Model::FTile* Tile);

    FPoolRebuiltEvent& OnPoolRebuiltEvent();
    FTileAddedEvent& OnTileAddedEvent();
    FTileRemovedEvent& OnTileRemovedEvent();

    virtual void Load() override;

protected:
    virtual void BeginPlay() override;

private:
    void SortAvailableTiles();

protected:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    ATileRegistry* TileRegistry;

private:
    TArray<const Model::FTile*> AvailableTiles;
    TArray<const Model::FTile*> UnavailableTiles;

    FPoolRebuiltEvent PoolRebuiltEvent;
    FTileAddedEvent TileAddedEvent;
    FTileRemovedEvent TileRemovedEvent;
};
