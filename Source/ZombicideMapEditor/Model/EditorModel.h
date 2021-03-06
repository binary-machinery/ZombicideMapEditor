#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapData/Map.h"
#include "MapData/MapTileRotation.h"
#include "ZombicideMapEditor/ILoadable.h"
#include "EditorModel.generated.h"

class ASettings;
class ATilePool;
class AMapGenerator;

namespace Model
{
    class FTileId;
}

UCLASS()
class ZOMBICIDEMAPEDITOR_API AEditorModel : public AActor, public ILoadable
{
    GENERATED_BODY()

public:
    DECLARE_EVENT(AEditorModel, FMapUpdatedEvent)

    const Model::FMap& GetMap() const;
    void GenerateNextTile();
    void RegenerateMap();

    void SetMapTile(const uint32 X, const uint32 Y, const Model::FTileId& TileId,
                    const Model::EMapTileRotation Rotation);
    void ResetMapTile(const uint32 X, const uint32 Y);
    void ResetMapTiles();

    FMapUpdatedEvent& OnMapUpdatedEvent();

    virtual void Load() override;

protected:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    ASettings* Settings;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    ATilePool* TilePool;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Dependencies")
    AMapGenerator* MapGenerator;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float GenerateNextTileTimeInterval = 0.2f;

private:
    void CreateMap();

private:
    TUniquePtr<Model::FMap> Map;

    bool bGenerated = false;
    FTimerHandle GenerateNextTileTimerHandle;

    FMapUpdatedEvent MapUpdatedEvent;
};
