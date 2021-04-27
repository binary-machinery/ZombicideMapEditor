#include "TileSpriteActor.h"
#include "PaperSpriteComponent.h"
#include "Paper2D/Classes/PaperSprite.h"

// Sets default values
ATileSpriteActor::ATileSpriteActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
    SpriteComponent->SetRelativeScale3D(FVector(0.5f));
    RootComponent = SpriteComponent;
}

void ATileSpriteActor::SetSprite(UPaperSprite* Sprite)
{
    SpriteComponent->SetSprite(Sprite);
}

// Called when the game starts or when spawned
void ATileSpriteActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ATileSpriteActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
