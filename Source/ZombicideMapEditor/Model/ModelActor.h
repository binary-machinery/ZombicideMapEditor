// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MapGenerator.h"
#include "TilePool.h"
#include "TileRegistry.h"
#include "GameFramework/Actor.h"
#include "MapData/Map.h"

#include "ModelActor.generated.h"

UCLASS()
class ZOMBICIDEMAPEDITOR_API AModelActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AModelActor();

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
