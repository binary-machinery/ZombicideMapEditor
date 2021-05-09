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
    ATilePool();
    const TArray<const Model::FTile*>& GetAvailableTiles() const;
    const Model::FTile* TakeTileFromPool(const Model::FTileId& TileId);
    const Model::FTile* TakeRandomTileFromPool();
    void ReturnTileToPool(const Model::FTile* Tile);

    virtual void PostInitializeComponents() override;

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
    ATileRegistry* TileRegistry;

private:
    TArray<const Model::FTile*> AvailableTiles;
    TArray<const Model::FTile*> UnavailableTiles;
};
