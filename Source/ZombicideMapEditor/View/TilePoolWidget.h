#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "TilePoolWidget.generated.h"

class UTilePoolItemWidget;
class UWrapBox;

UCLASS()
class ZOMBICIDEMAPEDITOR_API UTilePoolWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void ClearTilePoolItemWidgets();
    void AddTilePoolItemWidget(UTilePoolItemWidget* TilePoolItemWidget);

protected:
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UWrapBox* TilePoolItemsContainer;
};
