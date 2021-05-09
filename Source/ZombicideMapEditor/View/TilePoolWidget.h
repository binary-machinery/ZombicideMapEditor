#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "TilePoolWidget.generated.h"

namespace Model {
    class FTileId;
}

class UTilePoolItemWidget;
class UPanelWidget;

UCLASS()
class ZOMBICIDEMAPEDITOR_API UTilePoolWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void ClearTilePoolItemWidgets();
    void RemoveTilePoolItemWidget(const Model::FTileId& TileId);
    void AddTilePoolItemWidget(UTilePoolItemWidget* TilePoolItemWidget);
    void SortTilePoolItemWidgets();

protected:
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UPanelWidget* TilePoolItemsContainer;
};
