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
    TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TileId"));
    TextRenderComponent->HorizontalAlignment = EHTA_Center;
    TextRenderComponent->VerticalAlignment = EVRTA_TextCenter;
    TextRenderComponent->SetupAttachment(RootComponent);

    SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
    SpriteComponent->SetRelativeScale3D(FVector(0.5f));
    RootComponent = SpriteComponent;
}

void ATileSpriteActor::SetTileData(const Model::FTileId& TileIdValue, UPaperSprite* Sprite)
{
    TileId = TileIdValue;
    SpriteComponent->SetSprite(Sprite);
    TextRenderComponent->SetText(FText::FromString(TileId.ToString()));
}

void ATileSpriteActor::SetPosition(const float X, const float Y)
{
    SetActorLocation(FVector(X, 0, Y));
    TextRenderComponent->SetWorldLocation(FVector(X, 1, Y));
    TextRenderComponent->SetWorldRotation(FRotator::MakeFromEuler(FVector(0, 0, 90)));
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
    SpriteComponent->SetRelativeRotation(
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
