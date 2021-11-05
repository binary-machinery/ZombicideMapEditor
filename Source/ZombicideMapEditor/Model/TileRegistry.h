#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileData/Tile.h"
#include "ZombicideMapEditor/ILoadable.h"
#include "TileRegistry.generated.h"

class ASettings;

UCLASS()
class ZOMBICIDEMAPEDITOR_API ATileRegistry : public AActor, public ILoadable
{
    GENERATED_BODY()

public:
    ATileRegistry();
    const TArray<const Model::FTile*>& GetTiles() const;

    virtual void Load() override;

protected:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    ASettings* Settings;

    virtual void BeginPlay() override;

private:
    TArray<Model::FTile> Tiles;
    TArray<const Model::FTile*> TilePointers;
};
