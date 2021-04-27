#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EditorViewActor.generated.h"

class ATileSpriteActor;
class UPaperSprite;

UCLASS()
class ZOMBICIDEMAPEDITOR_API AEditorViewActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AEditorViewActor();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UPaperSprite* TileSprite;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
