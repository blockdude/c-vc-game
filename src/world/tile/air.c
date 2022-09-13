#include "tile.h"

void air_init( void )
{
    struct tile *tile = tile_new( TILE_AIR );

	tile->solid = false;
}
