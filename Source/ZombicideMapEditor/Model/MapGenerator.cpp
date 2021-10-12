#include "MapGenerator.h"

#include "TilePool.h"
#include "MapData/Map.h"

std::array<Model::EMapTileRotation, 4> AMapGenerator::AvailableRotations = {
    Model::EMapTileRotation::Rotation0,
    Model::EMapTileRotation::Rotation90,
    Model::EMapTileRotation::Rotation180,
    Model::EMapTileRotation::Rotation270
};

AMapGenerator::AMapGenerator()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMapGenerator::SetMap(Model::FMap* Value)
{
    this->Map = Value;
}

void AMapGenerator::Generate()
{
    checkf(Map, TEXT("Map is null"));
    checkf(TilePool, TEXT("TilePool is null"));

    for (uint32 X = 0; X < Map->GetSizeX(); ++X)
    {
        for (uint32 Y = 0; Y < Map->GetSizeY(); ++Y)
        {
            Map->SetTile(
                X, Y,
                TilePool->TakeRandomTileFromPool(),
                AvailableRotations[FMath::RandHelper(AvailableRotations.size())]
            );
        }
    }
}

bool AMapGenerator::GenerateNextTile()
{
    const Model::FMapTile& CurrentMapTile = Map->GetMapTile(CurrentX, CurrentY);
    if (CurrentMapTile.GetTile())
    {
        TilePool->ReturnTileToPool(CurrentMapTile.GetTile());
    }

    Map->SetTile(
        CurrentX, CurrentY,
        TilePool->TakeRandomTileFromPool(),
        AvailableRotations[FMath::RandHelper(AvailableRotations.size())]
    );

    ++CurrentX;
    if (CurrentX >= Map->GetSizeX())
    {
        CurrentX = 0;
        ++CurrentY;
        if (CurrentY >= Map->GetSizeY())
        {
            CurrentY = 0;
            return true;
        }
    }
    return false;
}

void AMapGenerator::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("AMapGenerator::BeginPlay"));
}

void AMapGenerator::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    UE_LOG(LogTemp, Warning, TEXT("AMapGenerator::PostInitializeComponents"));
}

void AMapGenerator::Load()
{
    UE_LOG(LogTemp, Warning, TEXT("AMapGenerator::Load"));
}

void AMapGenerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
