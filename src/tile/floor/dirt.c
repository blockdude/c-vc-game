#include "../tile.h"

void dirt_init()
{
    struct Tile tile = DEFAULT_TILE;
    enum TileId id = TILE_DIRT;

    tile.id = id;
    tile.use_color = true;
    tile.color = 0x964B00FF;

    TILES[ id ] = tile;
}
