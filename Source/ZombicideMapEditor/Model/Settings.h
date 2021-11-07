#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombicideMapEditor/ILoadable.h"
#include "Settings.generated.h"

UCLASS()
class ZOMBICIDEMAPEDITOR_API ASettings : public AActor, public ILoadable
{
    GENERATED_BODY()

public:
    DECLARE_EVENT(ASettings, FMapSizeUpdatedEvent)

    DECLARE_EVENT_TwoParams(ASettings, FSetToggledEvent, const FString&, const bool)

    uint32 GetMapSizeX() const;
    uint32 GetMapSizeY() const;
    void SetMapSize(uint32 SizeX, uint32 SizeY);

    bool IsSetEnabled(const FString& Set) const;
    void SetSetEnabled(const FString& Set, const bool bIsEnabled);

    void AddAvailableSet(const FString& Set);
    const TArray<FString>& GetAvailableSets() const;

    FMapSizeUpdatedEvent& OnMapSizeUpdated();
    FSetToggledEvent& OnSetToggledEvent();

    virtual void Load() override;

private:
    TArray<FString> AvailableSets;
    TMap<FString, bool> EnabledSets;

    uint32 MapSizeX;
    uint32 MapSizeY;

    FMapSizeUpdatedEvent MapSizeUpdated;
    FSetToggledEvent SetToggledEvent;
};
