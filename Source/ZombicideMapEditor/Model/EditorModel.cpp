// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorModel.h"

#include "MapGenerator.h"

AEditorModel::AEditorModel()
{
    PrimaryActorTick.bCanEverTick = true;
}

const Model::FMap& AEditorModel::GetMap() const
{
    return *Map;
}

void AEditorModel::GenerateNextTile()
{
    MapGenerator->GenerateNextTile();
    GeneratedNextTileEvent.Broadcast();
}

AEditorModel::FGeneratedMapEvent& AEditorModel::OnGeneratedMapEvent()
{
    return GeneratedMapEvent;
}

AEditorModel::FGeneratedNextTileEvent& AEditorModel::OnGeneratedNextTileEvent()
{
    return GeneratedNextTileEvent;
}

void AEditorModel::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    UE_LOG(LogTemp, Warning, TEXT("AEditorModel::PostInitializeComponents"));

    if (GetWorld()->IsGameWorld())
    {
        Map = MakeUnique<Model::FMap>(3, 3);
        MapGenerator->SetMap(Map.Get());
    }
}

void AEditorModel::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("AEditorModel::BeginPlay"));

    GetWorldTimerManager().SetTimer(GenerateNextTileTimerHandle, this, &AEditorModel::GenerateNextTile,
                                    GenerateNextTileTimeInterval, true, GenerateNextTileTimeInterval);
}

void AEditorModel::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bGenerated)
    {
        MapGenerator->Generate();
        bGenerated = true;
        GeneratedMapEvent.Broadcast();
    }
}
