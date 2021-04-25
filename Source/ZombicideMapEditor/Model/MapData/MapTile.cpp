#include "MapTile.h"
#include "ZombicideMapEditor/Model/TileData/Tile.h"

Model::FMapTile::FMapTile(const FTile* const Tile, const EMapTileRotation Rotation)
    : Tile(Tile),
      Rotation(Rotation)
{
}
