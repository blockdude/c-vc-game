#include "tile.h"

void dirt_init( void )
{
    struct tile tile = DEFAULT_TILE;
    enum tile_id id = TILE_DIRT;

    tile.id = id;
    tile.use_color = true;
    tile.color = 0x964B00FF;

    TILES[ id ] = tile;
}
