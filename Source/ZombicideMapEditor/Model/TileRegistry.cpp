#include "TileRegistry.h"

ATileRegistry::ATileRegistry()
{
}

const TArray<const Model::FTile*>& ATileRegistry::GetTiles() const
{
    return TilePointers;
}

void ATileRegistry::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    UE_LOG(LogTemp, Warning, TEXT("ATileRegistry::PostInitializeComponents"));

    // TODO: load the tile config file
    Tiles.Emplace(1, 1, Model::ETileSide::V);
    Tiles.Emplace(1, 2, Model::ETileSide::R);
    Tiles.Emplace(1, 3, Model::ETileSide::R);
    Tiles.Emplace(1, 4, Model::ETileSide::V);
    Tiles.Emplace(1, 5, Model::ETileSide::R);
    Tiles.Emplace(1, 6, Model::ETileSide::R);
    Tiles.Emplace(1, 8, Model::ETileSide::V);
    Tiles.Emplace(1, 9, Model::ETileSide::R);
    Tiles.Emplace(1, 9, Model::ETileSide::V);
    Tiles.Emplace(1, 10, Model::ETileSide::R);
    Tiles.Emplace(1, 10, Model::ETileSide::V);
    Tiles.Emplace(1, 11, Model::ETileSide::R);
    Tiles.Emplace(1, 11, Model::ETileSide::V);
    Tiles.Emplace(1, 12, Model::ETileSide::R);
    Tiles.Emplace(1, 13, Model::ETileSide::R);
    Tiles.Emplace(1, 14, Model::ETileSide::R);
    Tiles.Emplace(1, 15, Model::ETileSide::R);
    Tiles.Emplace(1, 16, Model::ETileSide::R);
    Tiles.Emplace(1, 17, Model::ETileSide::R);
    Tiles.Emplace(1, 18, Model::ETileSide::R);
    Tiles.Emplace(1, 19, Model::ETileSide::R);
    Tiles.Emplace(1, 20, Model::ETileSide::R);
    Tiles.Emplace(1, 21, Model::ETileSide::R);
    Tiles.Emplace(1, 22, Model::ETileSide::R);
    Tiles.Emplace(1, 23, Model::ETileSide::R);
    Tiles.Emplace(1, 24, Model::ETileSide::R);

    for (const Model::FTile& Tile : Tiles)
    {
        TilePointers.Add(&Tile);
    }
}

void ATileRegistry::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("ATileRegistry::BeginPlay"));
}
