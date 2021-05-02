#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
    // Sets default values for this actor's properties
    AEditorViewActor();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    AEditorModelActor* ModelActor;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<UPaperSprite*> TileSprites;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    void RedrawMap();
    void SpawnSprite(const uint32 X, const uint32 Y, const Model::FTileId& TileId);

    TMap<Model::FTileId, UPaperSprite*> TileSpritesMap;
    TArray<ATileSpriteActor*> TileSpriteActors;
};
