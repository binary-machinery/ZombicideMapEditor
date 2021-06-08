#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ZombicideMapEditor/Model/TileData/TileId.h"

#include "TilePoolItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;
class UTexture2D;

UCLASS()
class ZOMBICIDEMAPEDITOR_API UTilePoolItemWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    DECLARE_EVENT_OneParam(UTilePoolItemWidget, FClickedEvent, const Model::FTileId&)

    void SetTileId(const Model::FTileId& TileId);
    void SetTileTexture(UTexture2D* Texture);

    const Model::FTileId& GetTileId() const;

    FClickedEvent& OnClickedEvent();

protected:
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UImage* Sprite;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
    UTextBlock* IdText;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, BlueprintSetter=SetWidgetButton)
    UButton* WidgetButton;

    UFUNCTION(BlueprintSetter)
    void SetWidgetButton(UButton* Button);

    UFUNCTION()
    void OnButtonClicked();

private:
    Model::FTileId TileId;

    FClickedEvent ClickedEvent;
};
