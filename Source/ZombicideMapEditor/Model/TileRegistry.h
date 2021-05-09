#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileData/Tile.h"
#include "TileRegistry.generated.h"

UCLASS()
class ZOMBICIDEMAPEDITOR_API ATileRegistry : public AActor
{
    GENERATED_BODY()

public:
    ATileRegistry();
    const TArray<const Model::FTile*>& GetTiles() const;

    virtual void PostInitializeComponents() override;

protected:
    virtual void BeginPlay() override;

private:
    TArray<Model::FTile> Tiles;
    TArray<const Model::FTile*> TilePointers;
};
