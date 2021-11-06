#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombicideMapEditor/Model/MapData/MapTileRotation.h"
#include "ZombicideMapEditor/Model/TileData/TileId.h"
#include "ZombicideMapEditor/ILoadable.h"
#include "EditorView.generated.h"

class UGenerationWidget;
class ASettings;
class USettingsWidget;
class ATilePool;
class UUiWidget;
class UTilePoolWidget;
class UTilePoolItemWidget;
class AEditorModel;
class ATileSpriteActor;
class UPaperSprite;

namespace Model
{
    class FTileId;
}

UCLASS()
class ZOMBICIDEMAPEDITOR_API AEditorView : public AActor, public ILoadable
{
    GENERATED_BODY()

public:
    AEditorView();

    virtual void Load() override;

public:
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MapOffsetX = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MapOffsetY = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MapTileSize = 250;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TArray<UPaperSprite*> TileSprites;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUiWidget> UiWidgetType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UTilePoolWidget> TilePoolWidgetType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UTilePoolItemWidget> TilePoolItemWidgetType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UGenerationWidget> GenerationWidgetType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<USettingsWidget> SettingsWidgetType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<ATileSpriteActor> MapTileActorType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<ATileSpriteActor> SelectedTileActorType;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    ASettings* Settings;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    AEditorModel* ModelActor;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    ATilePool* TilePool;

    UFUNCTION()
    void OnMouseLeftButtonClick();

    UFUNCTION()
    void OnMouseRightButtonClick();

private:
    void RedrawMap();
    void SpawnSprite(const uint32 X, const uint32 Y, const Model::FTileId& TileId,
                     const Model::EMapTileRotation Rotation);

    void RebuildTilePoolItemWidgets();
    void AddTilePoolItemWidget(const Model::FTileId& TileId);
    void RemoveTilePoolItemWidget(const Model::FTileId& TileId);

    void OnSelectedTileChanged(const Model::FTileId& TileId);

    float GetAdjustedMapOffsetX() const;
    float GetAdjustedOffsetY() const;

    int32 WorldXToGridIndexX(const float WorldX);
    int32 WorldZToGridIndexY(const float WorldZ);
    float GridIndexXToWorldX(const int32 GridIndexX);
    float GridIndexYToWorldZ(const int32 GridIndexY);

    TMap<Model::FTileId, UPaperSprite*> TileSpritesMap;
    TArray<ATileSpriteActor*> TileSpriteActors;
    ATileSpriteActor* SelectedTileSpriteActor;
    UUiWidget* UiWidget;
    UTilePoolWidget* TilePoolWidget;
    UGenerationWidget* GenerationWidget;
    USettingsWidget* SettingsWidget;
};
