#include "LoadingManager.h"

#include "Model/EditorModel.h"
#include "Model/MapGenerator.h"
#include "Model/Settings.h"
#include "Model/TilePool.h"
#include "Model/TileRegistry.h"
#include "View/EditorView.h"

void ALoadingManager::BeginPlay()
{
    Super::BeginPlay();
    Settings->Load();
    TileRegistry->Load();
    TilePool->Load();
    MapGenerator->Load();
    EditorModel->Load();
    EditorView->Load();
}
