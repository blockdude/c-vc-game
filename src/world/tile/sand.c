#include "tile.h"

void sand_init( void )
{
    struct tile tile = DEFAULT_TILE;
    enum tile_id id = TILE_SAND;

    tile.id = id;
    tile.use_color = true;
    tile.color = 0xC2B280FF;

    TILES[ id ] = tile;
}
