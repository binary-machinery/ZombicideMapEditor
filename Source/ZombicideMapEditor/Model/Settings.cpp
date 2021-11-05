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

void ASettings::AddAvailableSet(const FString& Set)
{
    if (!AvailableSets.Contains(Set))
    {
        AvailableSets.Add(Set);
    }
}

const TArray<FString>& ASettings::GetAvailableSets() const
{
    return AvailableSets;
}

ASettings::FMapSizeUpdated& ASettings::OnMapSizeUpdated()
{
    return MapSizeUpdated;
}

void ASettings::Load()
{
    UE_LOG(LogTemp, Warning, TEXT("ASettings::Load"));
    // TODO: load persistent settings
    MapSizeX = 3;
    MapSizeY = 3;
}

void ASettings::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("ASettings::BeginPlay"));
}
