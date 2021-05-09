#include "TilePoolItemWidget.h"

#include "Components/Image.h"

void UTilePoolItemWidget::SetSpriteTexture(UTexture2D* Texture)
{
    Sprite->SetBrushFromTexture(Texture);
}
