#include "TilePoolWidget.h"

#include "TilePoolItemWidget.h"
#include "Components/WrapBox.h"

void UTilePoolWidget::ClearTilePoolItemWidgets()
{
    TilePoolItemsContainer->ClearChildren();
}

void UTilePoolWidget::RemoveTilePoolItemWidget(const Model::FTileId& TileId)
{
    for (int32 i = 0; i < TilePoolItemsContainer->GetChildrenCount(); ++i)
    {
        UTilePoolItemWidget* TilePoolWidget = Cast<UTilePoolItemWidget>(TilePoolItemsContainer->GetChildAt(i));
        if (TilePoolWidget->GetTileId() == TileId)
        {
            TilePoolItemsContainer->RemoveChildAt(i);
            break;
        }
    }
}

void UTilePoolWidget::AddTilePoolItemWidget(UTilePoolItemWidget* TilePoolItemWidget)
{
    TilePoolItemsContainer->AddChild(TilePoolItemWidget);
}

void UTilePoolWidget::SortTilePoolItemWidgets()
{
    TArray<UTilePoolItemWidget*> TilePoolItemWidgets;
    for (UWidget* Widget : TilePoolItemsContainer->GetAllChildren())
    {
        TilePoolItemWidgets.Add(Cast<UTilePoolItemWidget>(Widget));
    }
    TilePoolItemsContainer->ClearChildren();

    TilePoolItemWidgets.Sort([](const UTilePoolItemWidget& Widget1, const UTilePoolItemWidget& Widget2)
    {
        return Widget1.GetTileId() < Widget2.GetTileId();
    });

    for (UTilePoolItemWidget* Widget : TilePoolItemWidgets)
    {
        TilePoolItemsContainer->AddChild(Widget);
    }
}
