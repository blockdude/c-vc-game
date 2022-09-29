#include <string.h>
#include "chunk.h"
#include "world.h"
#include "../gfx/render.h"
#include "../gfx/window.h"

int chunk_init( struct chunk *self, struct world *world, size_t index )
{
    // init all data of chunk to zero
    memset( self, 0, sizeof( struct chunk ) );

    // init new data
    self->world = world;
    self->index = index;

    self->tiles = calloc( CHUNK_VOLUME, sizeof( *self->tiles ) );

	return 0;
}

int chunk_free( struct chunk *self )
{
    free( self->tiles );
    // just set data to zero
    memset( self, 0, sizeof( struct chunk ) );

	return 0;
}

int chunk_render( struct chunk *self )
{
	if ( self == NULL )
		return -1;

    int screen_w;
    int screen_h;
    window_get_size( &screen_w, &screen_h );
    int screen_center_x = screen_w / 2;
    int screen_center_y = screen_h / 2;

	for ( int i = 0; i < CHUNK_SIZE_X * CHUNK_SIZE_Y; i++ )
	{
        //int z = i / ( dim_x * dim_y );
        int z = 14;
        int w = i % ( CHUNK_SIZE_X * CHUNK_SIZE_Y );
        int y = w / CHUNK_SIZE_X;
        int x = w % CHUNK_SIZE_X;

        // convert xyz into an index for chunk tile array
        int idx = ( z * CHUNK_SIZE_X * CHUNK_SIZE_Y ) + ( y * CHUNK_SIZE_X ) + x;

        // don't do any more if out of bounds
        if ( x < 0 || y < 0 || x >= CHUNK_SIZE_X || y >= CHUNK_SIZE_Y )
            continue;

        // convert xy into screen coordinates
        float rect_x = ( float ) ( ( x - self->world->camera.x ) * self->world->camera.scale + screen_center_x );
        float rect_y = ( float ) ( ( y - self->world->camera.y ) * self->world->camera.scale + screen_center_y );

        struct rectangle rect = {
            .x = rect_x,
            .y = rect_y,
            .w = self->world->camera.scale * CHUNK_SIZE_X,
            .h = self->world->camera.scale * CHUNK_SIZE_Y
        };

        // render stuff
        u8 r, g, b, a;
        struct tile *t = tile_get( self->tiles[ idx ].id );
        color_split( t->color, &r, &g, &b, &a );

        //render_set_color( r, g, b, a );
        //render_filled_rectangle( rect );

        render_set_color( 0, 0, 0, 255 );
        render_filled_rectangle( rect );
	}

    return 0;
}
