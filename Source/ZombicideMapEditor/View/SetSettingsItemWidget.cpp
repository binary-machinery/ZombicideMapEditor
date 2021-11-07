#include "SetSettingsItemWidget.h"

#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void USetSettingsItemWidget::SetSet(const FString& Value)
{
    Set = Value;
    if (TextBlock)
    {
        TextBlock->SetText(FText::FromString(Set));
    }
}

void USetSettingsItemWidget::SetIsChecked(const bool Value)
{
    IsChecked = Value;
    if (CheckBox)
    {
        CheckBox->SetIsChecked(IsChecked);
    }
}

USetSettingsItemWidget::FToggledEvent& USetSettingsItemWidget::OnToggledEvent()
{
    return ToggledEvent;
}

void USetSettingsItemWidget::SetCheckBox(UCheckBox* Value)
{
    CheckBox = Value;
    CheckBox->SetIsChecked(IsChecked);
    CheckBox->OnCheckStateChanged.AddDynamic(this, &USetSettingsItemWidget::OnCheckBoxChecked);
}

void USetSettingsItemWidget::SetTextBlock(UTextBlock* Value)
{
    TextBlock = Value;
    TextBlock->SetText(FText::FromString(Set));
}

void USetSettingsItemWidget::OnCheckBoxChecked(bool bIsChecked)
{
    ToggledEvent.Broadcast(Set, bIsChecked);
}
