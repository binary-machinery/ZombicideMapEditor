#include "TilePoolWidget.h"

#include "TilePoolItemWidget.h"
#include "Components/WrapBox.h"

void UTilePoolWidget::ClearTilePoolItemWidgets()
{
    TilePoolItemsContainer->ClearChildren();
}

void UTilePoolWidget::AddTilePoolItemWidget(UTilePoolItemWidget* TilePoolItemWidget)
{
    TilePoolItemsContainer->AddChildToWrapBox(TilePoolItemWidget);
}
