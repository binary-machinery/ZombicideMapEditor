#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Settings.generated.h"

UCLASS()
class ZOMBICIDEMAPEDITOR_API ASettings : public AActor
{
    GENERATED_BODY()

public:
    DECLARE_EVENT(ASettings, FMapSizeUpdated)

    uint32 GetMapSizeX() const;
    uint32 GetMapSizeY() const;
    void SetMapSize(uint32 SizeX, uint32 SizeY);

    FMapSizeUpdated& OnMapSizeUpdated();

    virtual void PostInitializeComponents() override;

protected:
    virtual void BeginPlay() override;

private:
    uint32 MapSizeX;
    uint32 MapSizeY;

    FMapSizeUpdated MapSizeUpdated;
};
