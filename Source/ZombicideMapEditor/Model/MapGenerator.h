#pragma once

#include "CoreMinimal.h"
#include "MapData/MapTileRotation.h"
#include <array>
#include "GameFramework/Actor.h"
#include "ZombicideMapEditor/ILoadable.h"
#include "MapGenerator.generated.h"

class ATilePool;

namespace Model
{
    class FMap;
}

UCLASS()
class ZOMBICIDEMAPEDITOR_API AMapGenerator : public AActor, public ILoadable
{
    GENERATED_BODY()

public:
    void SetMap(Model::FMap* Value);
    void ResetIndices();
    bool GenerateNextTile();

protected:
    virtual void BeginPlay() override;

public:
    virtual void PostInitializeComponents() override;
    virtual void Load() override;

protected:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    ATilePool* TilePool;

private:
    static std::array<Model::EMapTileRotation, 4> AvailableRotations;

    Model::FMap* Map = nullptr;

    uint32 CurrentX = 0;
    uint32 CurrentY = 0;
};
