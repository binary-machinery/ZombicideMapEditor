#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UiWidget.generated.h"

class UWidgetSwitcher;
class UTilePoolWidget;

UCLASS()
class ZOMBICIDEMAPEDITOR_API UUiWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetTilePoolWidget(UTilePoolWidget* Widget);

protected:
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UWidgetSwitcher* TabsWidget;

private:
    UTilePoolWidget* TilePoolWidget;
};
