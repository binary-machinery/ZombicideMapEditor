#include "Settings.h"

uint32 ASettings::GetMapSizeX() const
{
    return MapSizeX;
}

uint32 ASettings::GetMapSizeY() const
{
    return MapSizeY;
}

void ASettings::SetMapSize(uint32 SizeX, uint32 SizeY)
{
    MapSizeX = SizeX;
    MapSizeY = SizeY;
    // TODO: persist
    MapSizeUpdated.Broadcast();
}

ASettings::FMapSizeUpdated& ASettings::OnMapSizeUpdated()
{
    return MapSizeUpdated;
}

void ASettings::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    UE_LOG(LogTemp, Warning, TEXT("ASettings::PostInitializeComponents"));
    // TODO: load persistent settings
}

void ASettings::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("ASettings::BeginPlay"));
}
