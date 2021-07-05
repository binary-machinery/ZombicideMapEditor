#include "TileSpriteActor.h"
#include "PaperSpriteComponent.h"
#include "Paper2D/Classes/PaperSprite.h"

std::array<Model::EMapTileRotation, 4> ATileSpriteActor::AvailableRotations = {
    Model::EMapTileRotation::Rotation0,
    Model::EMapTileRotation::Rotation90,
    Model::EMapTileRotation::Rotation180,
    Model::EMapTileRotation::Rotation270
};

// Sets default values
ATileSpriteActor::ATileSpriteActor()
{
    SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
    SpriteComponent->SetRelativeScale3D(FVector(0.5f));
    RootComponent = SpriteComponent;
}

void ATileSpriteActor::SetTileData(const Model::FTileId& TileIdValue, UPaperSprite* Sprite)
{
    TileId = TileIdValue;
    SpriteComponent->SetSprite(Sprite);
}

void ATileSpriteActor::Rotate()
{
    RotationIndex = (RotationIndex + 1) % AvailableRotations.size();
    SetActorRotation(FRotator::MakeFromEuler(FVector(0.0f, static_cast<float>(GetRotation()), 0.0f)));
}

const Model::FTileId& ATileSpriteActor::GetTileId() const
{
    return TileId;
}

Model::EMapTileRotation ATileSpriteActor::GetRotation() const
{
    return AvailableRotations[RotationIndex];
}
