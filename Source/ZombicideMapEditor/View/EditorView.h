#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombicideMapEditor/Model/MapData/MapTileRotation.h"
#include "ZombicideMapEditor/Model/TileData/TileId.h"

#include "EditorView.generated.h"

class ATilePool;
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
class ZOMBICIDEMAPEDITOR_API AEditorView : public AActor
{
    GENERATED_BODY()

public:
    AEditorView();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MapOffsetX = -250;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MapOffsetY = -125;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MapTileSize = 250;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TArray<UPaperSprite*> TileSprites;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UTilePoolWidget> TilePoolWidgetType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UTilePoolItemWidget> TilePoolItemWidgetType;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    AEditorModel* ModelActor;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    ATilePool* TilePool;

    UFUNCTION()
    void OnMouseLeftButtonClick();

private:
    void RedrawMap();
    void SpawnSprite(const uint32 X, const uint32 Y, const Model::FTileId& TileId,
                     const Model::EMapTileRotation Rotation);

    void RebuildTilePoolItemWidgets();
    void AddTilePoolItemWidget(const Model::FTileId& TileId);
    void RemoveTilePoolItemWidget(const Model::FTileId& TileId);

    void OnSelectedTileChanged(const Model::FTileId& TileId);

    uint32 WorldXToGridIndexX(const float WorldX);
    uint32 WorldZToGridIndexY(const float WorldZ);
    float GridIndexXToWorldX(const uint32 GridIndexX);
    float GridIndexYToWorldZ(const uint32 GridIndexY);

    TMap<Model::FTileId, UPaperSprite*> TileSpritesMap;
    TArray<ATileSpriteActor*> TileSpriteActors;
    ATileSpriteActor* SelectedTileSpriteActor;
    UTilePoolWidget* TilePoolWidget;
};
