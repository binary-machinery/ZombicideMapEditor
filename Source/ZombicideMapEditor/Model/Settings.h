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
    DECLARE_EVENT(ASettings, FMapSizeUpdated)

    uint32 GetMapSizeX() const;
    uint32 GetMapSizeY() const;
    void SetMapSize(uint32 SizeX, uint32 SizeY);

    FMapSizeUpdated& OnMapSizeUpdated();

    virtual void PostInitializeComponents() override;
    virtual void Load() override;

protected:
    virtual void BeginPlay() override;

private:
    uint32 MapSizeX = 3;
    uint32 MapSizeY = 3;

    FMapSizeUpdated MapSizeUpdated;
};