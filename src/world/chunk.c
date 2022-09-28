#include <string.h>
#include "chunk.h"
#include "world.h"
#include "../gfx/render.h"
#include "../gfx/window.h"

int chunk_init( struct chunk *self, struct world *world, i64 x, i64 y, i64 z )
{
    // init all data of chunk to zero
    memset( self, 0, sizeof( struct chunk ) );

    // init new data
    self->world = world;
    self->x = x;
    self->y = y;
    self->z = z;

	return 0;
}

int chunk_free( struct chunk *self )
{
    // just set data to zero
    memset( self, 0, sizeof( struct chunk ) );

	return 0;
}

int chunk_render( struct chunk *self )
{
	if ( self == NULL )
		return -1;

	for ( int i = 0; i < CHUNK_VOLUME; i++ )
	{
        int w, h;
        window_get_size( &w, &h );
	}

    return 0;
}
