#include "../tile.h"

void grass_init()
{
    struct Tile tile = DEFAULT_TILE;
    enum TileId id = TILE_GRASS;

    tile.id = id;
    tile.use_color = true;
    tile.color = 0x00FF00FF;

    TILES[ id ] = tile;
}
