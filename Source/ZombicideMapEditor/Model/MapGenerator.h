#pragma once

#include "CoreMinimal.h"
#include "MapData/MapTileRotation.h"
#include <array>
#include "GameFramework/Actor.h"
#include "MapGenerator.generated.h"

class ATilePool;

namespace Model
{
    class FMap;
}

UCLASS()
class ZOMBICIDEMAPEDITOR_API AMapGenerator : public AActor
{
    GENERATED_BODY()

public:
    AMapGenerator();
    void SetMap(Model::FMap* Value);
    void Generate();
    void GenerateNextTile();

protected:
    virtual void BeginPlay() override;

public:
    virtual void PostInitializeComponents() override;
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
    ATilePool* TilePool;

private:
    static std::array<Model::EMapTileRotation, 4> AvailableRotations;

    Model::FMap* Map = nullptr;

    uint32 CurrentX = 0;
    uint32 CurrentY = 0;
};
