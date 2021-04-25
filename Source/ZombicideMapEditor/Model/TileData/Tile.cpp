#include "Tile.h"

Model::FTile::FTile(const uint32_t SetId, const uint32_t CardId, const ETileSide Side)
    : SetId(SetId),
      TileId(CardId, Side)
{
}
