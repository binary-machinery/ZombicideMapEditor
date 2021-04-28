#include "EditorViewActor.h"

#include "PaperSprite.h"
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

    for (UPaperSprite* TileSprite : TileSprites)
    {
        FString TileName = TileSprite->GetName();
        const Model::ETileSide TileSide = TileName[TileName.Len() - 1] == 'V'
                                              ? Model::ETileSide::V
                                              : Model::ETileSide::R;
        TileName.LeftChopInline(1);
        const int32 CardId = FCString::Atoi(*TileName);
        TileSpritesMap.Add(Model::FTileId(CardId, TileSide), TileSprite);
    }

    ATileSpriteActor* TileSpriteActor = GetWorld()->SpawnActor<ATileSpriteActor>(ATileSpriteActor::StaticClass());
    TileSpriteActor->SetSprite(TileSpritesMap[Model::FTileId(8, Model::ETileSide::V)]);
}

// Called every frame
void AEditorViewActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
