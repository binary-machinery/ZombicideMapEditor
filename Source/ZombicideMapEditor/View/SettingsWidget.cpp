#include "SettingsWidget.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Misc/DefaultValueHelper.h"
#include "ZombicideMapEditor/Model/Settings.h"

void USettingsWidget::SetSettings(ASettings* Value)
{
    Settings = Value;
    MapSizeXInput->SetText(FText::FromString(FString::FromInt(Settings->GetMapSizeX())));
    MapSizeYInput->SetText(FText::FromString(FString::FromInt(Settings->GetMapSizeY())));
}

void USettingsWidget::SetApplySizeButton(UButton* Button)
{
    ApplySizeButton = Button;
    ApplySizeButton->OnClicked.AddDynamic(this, &USettingsWidget::ApplyMapSize);
}

void USettingsWidget::ApplyMapSize()
{
    if (!MapSizeXInput->GetText().IsNumeric())
    {
        MapSizeXInput->SetText(FText::FromString(TEXT("Error")));
        return;
    }

    if (!MapSizeYInput->GetText().IsNumeric())
    {
        MapSizeYInput->SetText(FText::FromString(TEXT("Error")));
        return;
    }

    int32 SizeX;
    int32 SizeY;
    FDefaultValueHelper::ParseInt(MapSizeXInput->GetText().ToString(), SizeX);
    FDefaultValueHelper::ParseInt(MapSizeYInput->GetText().ToString(), SizeY);
    Settings->SetMapSize(SizeX, SizeY);
}
