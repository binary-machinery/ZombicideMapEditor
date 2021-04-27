#include "EditorViewActor.h"
#include "TileSpriteActor.h"

// Sets default values
AEditorViewActor::AEditorViewActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEditorViewActor::BeginPlay()
{
    Super::BeginPlay();

    ATileSpriteActor* TileSpriteActor = GetWorld()->SpawnActor<ATileSpriteActor>(ATileSpriteActor::StaticClass());
    TileSpriteActor->SetSprite(TileSprite);
}

// Called every frame
void AEditorViewActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
