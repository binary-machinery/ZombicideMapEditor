#include "TilePoolItemWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

void UTilePoolItemWidget::SetTileId(const Model::FTileId& TileId)
{
    IdText->SetText(FText::FromString(TileId.ToString()));
}

void UTilePoolItemWidget::SetTileTexture(UTexture2D* Texture)
{
    Sprite->SetBrushFromTexture(Texture);
}
