#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"

class ASettings;
class UEditableTextBox;

UCLASS()
class ZOMBICIDEMAPEDITOR_API USettingsWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetSettings(ASettings* Value);

protected:
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UEditableTextBox* MapSizeXInput;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UEditableTextBox* MapSizeYInput;

private:
    ASettings* Settings;
};
