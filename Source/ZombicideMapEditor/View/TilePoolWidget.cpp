#include "TilePoolWidget.h"

#include "TilePoolItemWidget.h"
#include "Components/WrapBox.h"

void UTilePoolWidget::AddTilePoolItemWidget(UTilePoolItemWidget* TilePoolItemWidget)
{
    TilePoolItemsContainer->AddChildToWrapBox(TilePoolItemWidget);
}
