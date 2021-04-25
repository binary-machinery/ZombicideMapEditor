#pragma once

#include "CoreMinimal.h"

#include "MapGenerator.h"
#include "TilePool.h"
#include "TileRegistry.h"
#include "GameFramework/Actor.h"
#include "MapData/Map.h"

#include "EditorModelActor.generated.h"

UCLASS()
class ZOMBICIDEMAPEDITOR_API AEditorModelActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AEditorModelActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    TUniquePtr<Model::FMap> Map;
    Model::FTileRegistry TileRegistry;
    Model::FTilePool TilePool;
    Model::FMapGenerator MapGenerator;
};
