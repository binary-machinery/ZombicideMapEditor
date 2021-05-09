#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TilePool.generated.h"

class ATileRegistry;

namespace Model
{
    class FTileId;
    class FTile;
}

UCLASS()
class ZOMBICIDEMAPEDITOR_API ATilePool : public AActor
{
    GENERATED_BODY()

public:
    DECLARE_EVENT(ATilePool, FPoolRebuiltEvent)

    DECLARE_EVENT_TwoParams(ATilePool, FTileAddedEvent, const Model::FTileId&, uint32)

    DECLARE_EVENT_OneParam(ATilePool, FTileRemovedEvent, uint32)

    ATilePool();
    const TArray<const Model::FTile*>& GetAvailableTiles() const;
    const Model::FTile* TakeTileFromPool(const Model::FTileId& TileId);
    const Model::FTile* TakeRandomTileFromPool();
    void ReturnTileToPool(const Model::FTile* Tile);

    FPoolRebuiltEvent& OnPoolRebuiltEvent();
    FTileAddedEvent& OnTileAddedEvent();
    FTileRemovedEvent& OnTileRemovedEvent();

    virtual void PostInitializeComponents() override;

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
