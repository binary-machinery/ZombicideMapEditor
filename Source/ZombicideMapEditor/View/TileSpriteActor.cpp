#include "TileSpriteActor.h"
#include "PaperSpriteComponent.h"
#include "Components/TextRenderComponent.h"
#include "Paper2D/Classes/PaperSprite.h"

std::array<Model::EMapTileRotation, 4> ATileSpriteActor::AvailableRotations = {
    Model::EMapTileRotation::Rotation0,
    Model::EMapTileRotation::Rotation90,
    Model::EMapTileRotation::Rotation180,
    Model::EMapTileRotation::Rotation270
};

ATileSpriteActor::ATileSpriteActor()
{
    TileIdBackgroundSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TileIdBackground"));
    TileIdBackgroundSpriteComponent->SetupAttachment(RootComponent);

    TileIdTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TileId"));
    TileIdTextRenderComponent->HorizontalAlignment = EHTA_Center;
    TileIdTextRenderComponent->VerticalAlignment = EVRTA_TextCenter;
    TileIdTextRenderComponent->SetupAttachment(TileIdBackgroundSpriteComponent);

    TileSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
    TileSpriteComponent->SetRelativeScale3D(FVector(0.5f));
    RootComponent = TileSpriteComponent;
}

void ATileSpriteActor::SetTileData(const Model::FTileId& TileIdValue, UPaperSprite* Sprite)
{
    TileId = TileIdValue;
    TileSpriteComponent->SetSprite(Sprite);
    TileIdTextRenderComponent->SetText(FText::FromString(TileId.ToString()));
}

void ATileSpriteActor::SetPosition(const float X, const float Y)
{
    // Yes, I don't like it too
    // TODO: Refactor the component hierarchy
    SetActorLocation(FVector(X, 0, Y));
    TileIdBackgroundSpriteComponent->SetWorldLocation(FVector(X, 1, Y));
    TileIdTextRenderComponent->SetWorldLocation(FVector(X, 2, Y));
    TileIdTextRenderComponent->SetWorldRotation(FRotator::MakeFromEuler(FVector(0, 0, 90)));
}

void ATileSpriteActor::SetRotation(const Model::EMapTileRotation Rotation)
{
    for (uint32 i = 0; i < AvailableRotations.size(); ++i)
    {
        if (AvailableRotations[i] == Rotation)
        {
            RotationIndex = i;
            break;
        }
    }
    TileSpriteComponent->SetRelativeRotation(
        FRotator::MakeFromEuler(FVector(0.0f, -static_cast<float>(GetRotation()), 0.0f))
    );
}

void ATileSpriteActor::Rotate()
{
    RotationIndex = (RotationIndex + 1) % AvailableRotations.size();
    SetActorRotation(FRotator::MakeFromEuler(FVector(0.0f, -static_cast<float>(GetRotation()), 0.0f)));
}

const Model::FTileId& ATileSpriteActor::GetTileId() const
{
    return TileId;
}

Model::EMapTileRotation ATileSpriteActor::GetRotation() const
{
    return AvailableRotations[RotationIndex];
}
