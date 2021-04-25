// Fill out your copyright notice in the Description page of Project Settings.


#include "ModelActor.h"

// Sets default values
AModelActor::AModelActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    Map = MakeUnique<Model::FMap>(3, 3);
    MapGenerator.SetMap(Map.Get());
    MapGenerator.SetTilePool(&TilePool);

    TilePool.Init(TileRegistry);
}

// Called when the game starts or when spawned
void AModelActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AModelActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
