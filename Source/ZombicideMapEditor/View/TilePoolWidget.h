#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TilePoolWidget.generated.h"

class UWrapBox;
UCLASS()
class ZOMBICIDEMAPEDITOR_API UTilePoolWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	UWrapBox* TilePoolItemsContainer;
};
