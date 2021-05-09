#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ZombicideMapEditor/Model/TileData/TileId.h"

#include "TilePoolItemWidget.generated.h"

class UTextBlock;
class UImage;
class UTexture2D;

UCLASS()
class ZOMBICIDEMAPEDITOR_API UTilePoolItemWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetTileId(const Model::FTileId& TileId);
    void SetTileTexture(UTexture2D* Texture);

protected:
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UImage* Sprite;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UTextBlock* IdText;
};
