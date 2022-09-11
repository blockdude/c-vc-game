#include "tile.h"

void cobblestone_init( void )
{
    struct tile tile = DEFAULT_TILE;
    enum tile_id id = TILE_COBBLESTONE;

    tile.id = id;
    tile.use_color = true;
    tile.color = 0xADA7A9FF;
    tile.collides = true;
    tile.solid = true;

    TILES[ id ] = tile;
}
