#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TileSpriteActor.generated.h"

class UPaperSpriteComponent;
class UPaperSprite;

UCLASS()
class ZOMBICIDEMAPEDITOR_API ATileSpriteActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ATileSpriteActor();

    void SetSprite(UPaperSprite* Sprite);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UPaperSpriteComponent* SpriteComponent;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
