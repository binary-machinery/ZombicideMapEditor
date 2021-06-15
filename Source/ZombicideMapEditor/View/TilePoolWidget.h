#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "TilePoolWidget.generated.h"

namespace Model
{
    class FTileId;
}

class UTilePoolItemWidget;
class UPanelWidget;

UCLASS()
class ZOMBICIDEMAPEDITOR_API UTilePoolWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    DECLARE_EVENT_OneParam(UTilePoolWidget, FTileSelectedEvent, const Model::FTileId&)

    void ClearTilePoolItemWidgets();
    void RemoveTilePoolItemWidget(const Model::FTileId& TileId);
    void AddTilePoolItemWidget(UTilePoolItemWidget* TilePoolItemWidget);
    void SortTilePoolItemWidgets();

    FTileSelectedEvent& OnTileSelectedEvent();

protected:
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UPanelWidget* TilePoolItemsContainer;

private:
    FTileSelectedEvent TileSelectedEvent;
};
