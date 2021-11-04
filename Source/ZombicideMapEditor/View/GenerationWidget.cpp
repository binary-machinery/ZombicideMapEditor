#include "GenerationWidget.h"

#include "Components/Button.h"

UGenerationWidget::FRegenerateMapEvent& UGenerationWidget::OnRegenerateMapEvent()
{
    return RegenerateMapEvent;
}

void UGenerationWidget::SetRegenerateMapButton(UButton* Button)
{
    RegenerateMapButton = Button;
    RegenerateMapButton->OnClicked.AddDynamic(this, &UGenerationWidget::RegenerateMap);
}

void UGenerationWidget::RegenerateMap()
{
    RegenerateMapEvent.Broadcast();
}
