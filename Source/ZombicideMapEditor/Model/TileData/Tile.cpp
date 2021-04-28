#include "Tile.h"

Model::FTile::FTile(const uint32 SetId, const uint32 CardId, const ETileSide Side)
    : SetId(SetId),
      TileId(CardId, Side)
{
}
