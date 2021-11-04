#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GenerationWidget.generated.h"

class UButton;

UCLASS()
class ZOMBICIDEMAPEDITOR_API UGenerationWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    DECLARE_EVENT(UGenerationWidget, FRegenerateMapEvent)

    FRegenerateMapEvent& OnRegenerateMapEvent();

protected:
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, BlueprintSetter=SetRegenerateMapButton)
    UButton* RegenerateMapButton;

    UFUNCTION(BlueprintSetter)
    void SetRegenerateMapButton(UButton* Button);

    UFUNCTION()
    void RegenerateMap();

private:
    FRegenerateMapEvent RegenerateMapEvent;
};
