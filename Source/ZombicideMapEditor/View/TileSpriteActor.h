#pragma once

#include "CoreMinimal.h"

#include <array>

#include "GameFramework/Actor.h"
#include "ZombicideMapEditor/Model/TileData/TileId.h"
#include "ZombicideMapEditor/Model/MapData/MapTileRotation.h"

#include "TileSpriteActor.generated.h"

class UPaperSpriteComponent;
class UPaperSprite;

UCLASS()
class ZOMBICIDEMAPEDITOR_API ATileSpriteActor : public AActor
{
    GENERATED_BODY()

public:
    ATileSpriteActor();

    void SetTileData(const Model::FTileId& TileId, UPaperSprite* Sprite);
    void SetRotation(const Model::EMapTileRotation Rotation);
    void Rotate();

    const Model::FTileId& GetTileId() const;
    Model::EMapTileRotation GetRotation() const;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UPaperSpriteComponent* SpriteComponent;

private:
    static std::array<Model::EMapTileRotation, 4> AvailableRotations;

    Model::FTileId TileId;
    uint32 RotationIndex = 0;
};
