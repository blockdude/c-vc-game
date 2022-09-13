#include "tile.h"

void water_init( void )
{
    struct tile *tile = tile_get( TILE_WATER );

	tile->liquid = true;
	tile->solid = false;
	tile->use_color = true;
	tile->color = 0xD4F1F9FF;
	tile->drag = 10.0f;
}
