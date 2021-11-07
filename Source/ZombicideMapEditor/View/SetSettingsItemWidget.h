#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SetSettingsItemWidget.generated.h"

class UTextBlock;
class UCheckBox;
UCLASS()
class ZOMBICIDEMAPEDITOR_API USetSettingsItemWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    DECLARE_EVENT_TwoParams(USetSettingsItemWidget, FToggledEvent, const FString&, const bool)

    void SetSet(const FString& Value);
    void SetIsChecked(const bool Value);

    FToggledEvent& OnToggledEvent();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, BlueprintSetter=SetCheckBox)
    UCheckBox* CheckBox;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, BlueprintSetter=SetTextBlock)
    UTextBlock* TextBlock;

    UFUNCTION(BlueprintSetter)
    void SetCheckBox(UCheckBox* Value);

    UFUNCTION(BlueprintSetter)
    void SetTextBlock(UTextBlock* Value);

    UFUNCTION()
    void OnCheckBoxChecked(bool bIsChecked);

private:
    FString Set;
    bool IsChecked;

    FToggledEvent ToggledEvent;
};
