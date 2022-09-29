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

    //int chunk_z = self->index / ( CHUNK_SIZE_X * CHUNK_SIZE_Y );
    int chunk_w = self->index % ( self->world->world_size_x * self->world->world_size_y );
    int chunk_y = chunk_w / self->world->world_size_x;
    int chunk_x = chunk_w % self->world->world_size_x;

    for ( int i = 0; i < CHUNK_SIZE_X * CHUNK_SIZE_Y; i++ )
    {
        //int z = i / ( dim_x * dim_y );
        // tile position
        int z = 15;
        int w = i % ( CHUNK_SIZE_X * CHUNK_SIZE_Y );
        int y = w / CHUNK_SIZE_X;
        int x = w % CHUNK_SIZE_X;

        // convert xyz into an index for chunk tile array
        int tile_index = ( z * CHUNK_SIZE_X * CHUNK_SIZE_Y ) + i;

        // don't do any more if out of bounds
        if ( tile_index < 0 || tile_index > CHUNK_VOLUME - 1 )
            continue;

        // convert xy into screen coordinates
        float rect_x = ( float ) ( ( x - self->world->camera.x + ( CHUNK_SIZE_X * chunk_x ) ) * self->world->camera.scale + screen_center_x );
        float rect_y = ( float ) ( ( y - self->world->camera.y + ( CHUNK_SIZE_Y * chunk_y ) ) * self->world->camera.scale + screen_center_y );

        struct rectangle rect = {
            .x = rect_x,
            .y = rect_y,
            .w = self->world->camera.scale,
            .h = self->world->camera.scale
        };

        // render stuff
        u8 r, g, b, a;
        struct tile *t = tile_get( self->tiles[ tile_index ].id );
        color_split( t->color, &r, &g, &b, &a );

        render_set_color( r, g, b, a );
        render_filled_rectangle( rect );

        render_set_color( 0, 0, 0, 255 );
        render_rectangle( rect );
    }

    printf( " rendered in pos %d, %d\n", chunk_x, chunk_y );

    return 0;
}
