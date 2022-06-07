#include "tile.h"

void cobblestone_init()
{
    struct Tile tile = DEFAULT_TILE;
    enum TileId id = TILE_COBBLESTONE;

    tile.id = id;
    tile.use_color = true;
    tile.color = 0xADA7A9FF;
    tile.collides = true;
    tile.solid = true;

    TILES[ id ] = tile;
}
