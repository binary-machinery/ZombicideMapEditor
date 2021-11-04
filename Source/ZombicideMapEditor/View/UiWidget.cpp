#include "UiWidget.h"

#include "Components/WidgetSwitcher.h"
#include "SettingsWidget.h"
#include "TilePoolWidget.h"
#include "GenerationWidget.h"
#include "Components/Button.h"

void UUiWidget::SetTilePoolWidget(UTilePoolWidget* Widget)
{
    TilesTabPanel->AddChild(Widget);
}

void UUiWidget::SetGenerationWidget(UGenerationWidget* Widget)
{
    GeneratorTabPanel->AddChild(Widget);
}

void UUiWidget::SetSettingsWidget(USettingsWidget* Widget)
{
    SettingsTabPanel->AddChild(Widget);
}

void UUiWidget::InitTilesTabButton(UButton* Button)
{
    Button->OnClicked.AddDynamic(this, &UUiWidget::OpenTilesTab);
}

void UUiWidget::InitGeneratorTabButton(UButton* Button)
{
    Button->OnClicked.AddDynamic(this, &UUiWidget::OpenGeneratorTab);
}

void UUiWidget::InitSettingsTabButton(UButton* Button)
{
    Button->OnClicked.AddDynamic(this, &UUiWidget::OpenSettingsTab);
}

void UUiWidget::OpenTilesTab()
{
    TabsWidget->SetActiveWidgetIndex(0);
}

void UUiWidget::OpenGeneratorTab()
{
    TabsWidget->SetActiveWidgetIndex(1);
}

void UUiWidget::OpenSettingsTab()
{
    TabsWidget->SetActiveWidgetIndex(2);
}
