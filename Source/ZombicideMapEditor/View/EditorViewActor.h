#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombicideMapEditor/Model/MapData/MapTileRotation.h"
#include "ZombicideMapEditor/Model/TileData/TileId.h"

#include "EditorViewActor.generated.h"

class AEditorModelActor;
class ATileSpriteActor;
class UPaperSprite;

namespace Model
{
    class FTileId;
}

UCLASS()
class ZOMBICIDEMAPEDITOR_API AEditorViewActor : public AActor
{
    GENERATED_BODY()

public:
    AEditorViewActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    AEditorModelActor* ModelActor;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<UPaperSprite*> TileSprites;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MapOffsetX = -250;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MapOffsetY = -125;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MapTileSize = 250;

private:
    void RedrawMap();
    void SpawnSprite(const uint32 X, const uint32 Y, const Model::FTileId& TileId,
                     const Model::EMapTileRotation Rotation);

    TMap<Model::FTileId, UPaperSprite*> TileSpritesMap;
    TArray<ATileSpriteActor*> TileSpriteActors;
};
