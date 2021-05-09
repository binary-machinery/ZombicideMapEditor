#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TilePoolItemWidget.generated.h"

class UTexture2D;
class UImage;

UCLASS()
class ZOMBICIDEMAPEDITOR_API UTilePoolItemWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetSpriteTexture(UTexture2D* Texture);

protected:
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UImage* Sprite;
};
