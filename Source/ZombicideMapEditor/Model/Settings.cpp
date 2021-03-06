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

bool ASettings::IsSetEnabled(const FString& Set) const
{
    const bool* IsEnabledPtr = EnabledSets.Find(Set);
    return !IsEnabledPtr || *IsEnabledPtr;
}

void ASettings::SetSetEnabled(const FString& Set, const bool bIsEnabled)
{
    EnabledSets.FindOrAdd(Set) = bIsEnabled;
    SetToggledEvent.Broadcast(Set, bIsEnabled);
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

ASettings::FMapSizeUpdatedEvent& ASettings::OnMapSizeUpdated()
{
    return MapSizeUpdated;
}

ASettings::FSetToggledEvent& ASettings::OnSetToggledEvent()
{
    return SetToggledEvent;
}

void ASettings::Load()
{
    UE_LOG(LogTemp, Warning, TEXT("ASettings::Load"));
    // TODO: load persistent settings
    MapSizeX = 3;
    MapSizeY = 3;
}
