#include "TilePoolWidget.h"

#include "TilePoolItemWidget.h"
#include "Components/WrapBox.h"

void UTilePoolWidget::ClearTilePoolItemWidgets()
{
    TilePoolItemsContainer->ClearChildren();
}

void UTilePoolWidget::RemoveTilePoolItemWidget(const uint32 Index)
{
    TilePoolItemsContainer->RemoveChildAt(Index);
}

void UTilePoolWidget::AddTilePoolItemWidget(UTilePoolItemWidget* TilePoolItemWidget)
{
    TilePoolItemsContainer->AddChild(TilePoolItemWidget);
}

void UTilePoolWidget::InsertTilePoolItemWidget(UTilePoolItemWidget* TilePoolItemWidget, const uint32 Index)
{
    // UPanelWidget::InsertChildAt(...) doesn't work
    // This is a workaround
    TArray<UWidget*> Widgets = TilePoolItemsContainer->GetAllChildren();
    Widgets.Insert(TilePoolItemWidget, Index);
    TilePoolItemsContainer->ClearChildren();
    for (UWidget* Widget : Widgets)
    {
        TilePoolItemsContainer->AddChild(Widget);
    }
}
