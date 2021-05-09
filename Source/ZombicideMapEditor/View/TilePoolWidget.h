#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "TilePoolWidget.generated.h"

class UTilePoolItemWidget;
class UPanelWidget;

UCLASS()
class ZOMBICIDEMAPEDITOR_API UTilePoolWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void ClearTilePoolItemWidgets();
    void RemoveTilePoolItemWidget(const uint32 Index);
    void AddTilePoolItemWidget(UTilePoolItemWidget* TilePoolItemWidget);
    void InsertTilePoolItemWidget(UTilePoolItemWidget* TilePoolItemWidget, const uint32 Index);

protected:
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UPanelWidget* TilePoolItemsContainer;
};
