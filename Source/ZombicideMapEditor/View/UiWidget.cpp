#include "UiWidget.h"
#include "Components/WidgetSwitcher.h"
#include "TilePoolWidget.h"

void UUiWidget::SetTilePoolWidget(UTilePoolWidget* Widget)
{
    TilePoolWidget = Widget;
    TabsWidget->AddChild(TilePoolWidget);
}
