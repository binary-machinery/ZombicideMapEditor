#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LoadingManager.generated.h"

class AEditorView;
class AEditorModel;
class AMapGenerator;
class ASettings;
class ATilePool;
class ATileRegistry;

UCLASS()
class ZOMBICIDEMAPEDITOR_API ALoadingManager : public AActor
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    ASettings* Settings;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    ATileRegistry* TileRegistry;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    ATilePool* TilePool;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    AMapGenerator* MapGenerator;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    AEditorModel* EditorModel;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    AEditorView* EditorView;
};
