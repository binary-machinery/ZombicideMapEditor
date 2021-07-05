// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorModel.h"

#include "MapGenerator.h"
#include "TilePool.h"
#include "TileData/Tile.h"

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
    const bool bFinished = MapGenerator->GenerateNextTile();
    MapUpdatedEvent.Broadcast();

    if (bFinished)
    {
        GetWorldTimerManager().ClearTimer(GenerateNextTileTimerHandle);
    }
}

void AEditorModel::SetMapTile(const uint32 X, const uint32 Y, const Model::FTileId& TileId,
                              const Model::EMapTileRotation Rotation)
{
    const Model::FMapTile& CurrentMapTile = Map->GetMapTile(X, Y);
    if (CurrentMapTile.GetTile())
    {
        TilePool->ReturnTileToPool(CurrentMapTile.GetTile());
    }

    Map->SetTile(
        X, Y,
        TilePool->TakeTileFromPool(TileId),
        Rotation
    );
    MapUpdatedEvent.Broadcast();
}

AEditorModel::FMapUpdatedEvent& AEditorModel::OnMapUpdatedEvent()
{
    return MapUpdatedEvent;
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
}
