#include "TilePoolItemWidget.h"

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

const Model::FTileId& UTilePoolItemWidget::GetTileId() const
{
    return TileId;
}
