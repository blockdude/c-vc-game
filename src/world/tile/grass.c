#include "../tile.h"

void grass_init( void )
{
    struct tile tile = DEFAULT_TILE;
    enum tile_id id = TILE_GRASS;

    tile.id = id;
    tile.use_color = true;
    tile.color = 0x00FF00FF;

    TILES[ id ] = tile;
}
