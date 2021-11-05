#include "TileRegistry.h"

#include "Settings.h"

ATileRegistry::ATileRegistry()
{
}

const TArray<const Model::FTile*>& ATileRegistry::GetTiles() const
{
    return TilePointers;
}

void ATileRegistry::Load()
{
    UE_LOG(LogTemp, Warning, TEXT("ATileRegistry::Load"));

    const FString Path = FPaths::Combine(FPaths::ProjectContentDir(), FString("Config/Tiles.json"));
    FString JsonFile;
    FFileHelper::LoadFileToString(JsonFile, *Path);

    const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonFile);
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
    {
        const TArray<TSharedPtr<FJsonValue>>& TilesData = JsonObject->GetArrayField("tiles");
        for (const TSharedPtr<FJsonValue> JsonValue : TilesData)
        {
            const TSharedPtr<FJsonObject>& TileJsonObject = JsonValue->AsObject();
            FString Id = TileJsonObject->GetStringField("id");
            FString Set = TileJsonObject->GetStringField("set");
            Model::FTileId TileId = Model::FTileId::FromString(Id);
            Tiles.Emplace(TileId, Set);
        }
    }

    for (const Model::FTile& Tile : Tiles)
    {
        TilePointers.Add(&Tile);
        Settings->AddAvailableSet(Tile.GetSet());
    }
}

void ATileRegistry::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("ATileRegistry::BeginPlay"));
}
