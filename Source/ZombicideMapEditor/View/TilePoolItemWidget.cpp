#include "TilePoolItemWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UTilePoolItemWidget::SetTileId(const Model::FTileId& Value)
{
    TileId = Value;
    IdText->SetText(FText::FromString(TileId.ToString()));
}

void UTilePoolItemWidget::SetTileTexture(UTexture2D* Texture)
{
    Sprite->SetBrushFromTexture(Texture);
}

void UTilePoolItemWidget::SetWidgetButton(UButton* Button)
{
    WidgetButton = Button;
    WidgetButton->OnClicked.AddDynamic(this, &UTilePoolItemWidget::OnButtonClicked);
}

const Model::FTileId& UTilePoolItemWidget::GetTileId() const
{
    return TileId;
}

UTilePoolItemWidget::FClickedEvent& UTilePoolItemWidget::OnClickedEvent()
{
    return ClickedEvent;
}

void UTilePoolItemWidget::OnButtonClicked()
{
    ClickedEvent.Broadcast(TileId);
}
