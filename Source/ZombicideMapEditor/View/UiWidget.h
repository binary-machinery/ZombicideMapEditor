#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UiWidget.generated.h"

class UGenerationWidget;
class USettingsWidget;
class UButton;
class UWidgetSwitcher;
class UTilePoolWidget;

UCLASS()
class ZOMBICIDEMAPEDITOR_API UUiWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetTilePoolWidget(UTilePoolWidget* Widget);
    void SetGenerationWidget(UGenerationWidget* Widget);
    void SetSettingsWidget(USettingsWidget* Widget);

protected:
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UWidgetSwitcher* TabsWidget;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UPanelWidget* TilesTabPanel;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UPanelWidget* GeneratorTabPanel;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UPanelWidget* SettingsTabPanel;

protected:
    UFUNCTION(BlueprintCallable)
    void InitTilesTabButton(UButton* Button);

    UFUNCTION(BlueprintCallable)
    void InitGeneratorTabButton(UButton* Button);

    UFUNCTION(BlueprintCallable)
    void InitSettingsTabButton(UButton* Button);
    
    UFUNCTION()
    void OpenTilesTab();

    UFUNCTION()
    void OpenGeneratorTab();

    UFUNCTION()
    void OpenSettingsTab();
};
