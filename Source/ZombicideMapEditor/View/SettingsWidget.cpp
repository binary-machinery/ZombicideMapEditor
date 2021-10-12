#include "SettingsWidget.h"

#include "Components/EditableTextBox.h"
#include "ZombicideMapEditor/Model/Settings.h"

void USettingsWidget::SetSettings(ASettings* Value)
{
    Settings = Value;
    MapSizeXInput->SetText(FText::FromString(FString::FromInt(Settings->GetMapSizeX())));
    MapSizeYInput->SetText(FText::FromString(FString::FromInt(Settings->GetMapSizeY())));
}
