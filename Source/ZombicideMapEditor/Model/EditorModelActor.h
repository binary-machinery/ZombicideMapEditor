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
    DECLARE_EVENT(AEditorModelActor, FGeneratedMapEvent)

    DECLARE_EVENT(AEditorModelActor, FGeneratedNextTileEvent)

    // Sets default values for this actor's properties
    AEditorModelActor();

    FGeneratedMapEvent& OnGeneratedMapEvent();
    FGeneratedNextTileEvent& OnGeneratedNextTileEvent();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float GenerateNextTileTimeInterval = 0.2f;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    void GenerateNextTile();

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    const Model::FMap& GetMap() const
    {
        return *Map;
    };

private:
    TUniquePtr<Model::FMap> Map;
    Model::FTileRegistry TileRegistry;
    Model::FTilePool TilePool;
    Model::FMapGenerator MapGenerator;

    bool bGenerated = false;
    FTimerHandle GenerateNextTileTimerHandle;

    FGeneratedMapEvent GeneratedMapEvent;
    FGeneratedNextTileEvent GeneratedNextTileEvent;
};
