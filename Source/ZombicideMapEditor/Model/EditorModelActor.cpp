// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorModelActor.h"

#include "MapGenerator.h"

AEditorModelActor::AEditorModelActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

const Model::FMap& AEditorModelActor::GetMap() const
{
    return *Map;
}

void AEditorModelActor::GenerateNextTile()
{
    MapGenerator->GenerateNextTile();
    GeneratedNextTileEvent.Broadcast();
}

AEditorModelActor::FGeneratedMapEvent& AEditorModelActor::OnGeneratedMapEvent()
{
    return GeneratedMapEvent;
}

AEditorModelActor::FGeneratedNextTileEvent& AEditorModelActor::OnGeneratedNextTileEvent()
{
    return GeneratedNextTileEvent;
}

void AEditorModelActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    UE_LOG(LogTemp, Warning, TEXT("AEditorModelActor::PostInitializeComponents"));

    if (GetWorld()->IsGameWorld())
    {
        Map = MakeUnique<Model::FMap>(3, 3);
        MapGenerator->SetMap(Map.Get());
    }
}

void AEditorModelActor::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("AEditorModelActor::BeginPlay"));

    GetWorldTimerManager().SetTimer(GenerateNextTileTimerHandle, this, &AEditorModelActor::GenerateNextTile,
                                    GenerateNextTileTimeInterval, true, GenerateNextTileTimeInterval);
}

void AEditorModelActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bGenerated)
    {
        MapGenerator->Generate();
        bGenerated = true;
        GeneratedMapEvent.Broadcast();
    }
}
