#include "../tile.h"

void air_init( void )
{
    struct tile tile = DEFAULT_TILE;
    enum tile_id id = TILE_AIR;

    tile.id = id;
    tile.solid = false;

    TILES[ id ] = tile;
}
