#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapData/Map.h"

#include "EditorModelActor.generated.h"

class AMapGenerator;

UCLASS()
class ZOMBICIDEMAPEDITOR_API AEditorModelActor : public AActor
{
    GENERATED_BODY()

public:
    DECLARE_EVENT(AEditorModelActor, FGeneratedMapEvent)

    DECLARE_EVENT(AEditorModelActor, FGeneratedNextTileEvent)

    AEditorModelActor();

    const Model::FMap& GetMap() const;
    void GenerateNextTile();

    FGeneratedMapEvent& OnGeneratedMapEvent();
    FGeneratedNextTileEvent& OnGeneratedNextTileEvent();

    virtual void PostInitializeComponents() override;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    AMapGenerator* MapGenerator;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float GenerateNextTileTimeInterval = 0.2f;

private:
    TUniquePtr<Model::FMap> Map;

    bool bGenerated = false;
    FTimerHandle GenerateNextTileTimerHandle;

    FGeneratedMapEvent GeneratedMapEvent;
    FGeneratedNextTileEvent GeneratedNextTileEvent;
};
