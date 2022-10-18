#include <string.h>
#include "world.h"
#include "../gfx/render.h"
#include "../gfx/window.h"
#include "../input/input.h"

int world_init( struct world *self, size_t world_size_x, size_t world_size_y, size_t world_size_z )
{
    memset( self, 0, sizeof( struct world ) );

    self->world_size_x = world_size_x;
    self->world_size_y = world_size_y;
    self->world_size_z = world_size_z;
    self->chunks_count = world_size_x * world_size_y * world_size_z;
    self->chunks = calloc( self->chunks_count, sizeof( *self->chunks ) );

    for ( size_t i = 0; i < self->chunks_count; i++ )
        chunk_init( &self->chunks[ i ], self, i );

    self->camera.x = self->world_size_x * CHUNK_SIZE_X / 2;
    self->camera.y = self->world_size_y * CHUNK_SIZE_Y / 2;
    self->camera.scale = 5.0f;

    return 0;
}

int world_free( struct world *self )
{
    for ( size_t i = 0; i < self->chunks_count; i++ )
        chunk_free( &self->chunks[ i ] );

    free( self->chunks );
    memset( self, 0, sizeof( struct world ) );

    return 0;
}

int world_tick( struct world *self )
{
    if ( self == NULL )
        return -1;

    self->tick++;

    return 0;
}

int world_update( struct world *self )
{
    if ( self == NULL )
        return -1;
            
    return 0;
}

int world_render( struct world *self )
{
    if ( self == NULL )
        return -1;

    // get screen center
    int screen_center_x;
    int screen_center_y;

    window_get_size( &screen_center_x, &screen_center_y );

    screen_center_x = screen_center_x / 2;
    screen_center_y = screen_center_y / 2;

    float m[] = {
        -1.0f, -1.0f,
        -1.0f, 0.0f,
        -1.0f, 1.0f,

        0.0f, -1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,

        1.0f, -1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    for ( int i = 0; i < 9; i++ )
    {
        // get player z chunk coordinates
        int z = 0;

        // get xyz index
        int y = floor( self->camera.y / CHUNK_SIZE_Y ) + m[ i * 2 ];
        int x = floor( self->camera.x / CHUNK_SIZE_X ) + m[ i * 2 + 1 ];

        // convert xyz into an index for world chunk array
        int idx = ( z * self->world_size_x * self->world_size_y ) + ( y * self->world_size_x ) + x;

        // stop if out of bounds in array
        if ( x < 0 || y < 0 || x >= ( int ) self->world_size_x || y >= ( int ) self->world_size_y )
            continue;

        // convert world coordinates into screen coordinates
        float rect_x = ( float ) ( ( x * CHUNK_SIZE_X - self->camera.x ) * self->camera.scale + screen_center_x );
        float rect_y = ( float ) ( ( y * CHUNK_SIZE_Y - self->camera.y ) * self->camera.scale + screen_center_y );

        struct rectangle rect = {
            .x = rect_x,
            .y = rect_y,
            .w = self->camera.scale * CHUNK_SIZE_X,
            .h = self->camera.scale * CHUNK_SIZE_Y
        };

        // render stuff
        chunk_render( &self->chunks[ idx ] );

        // draw chunk outline
        render_set_color( 255, 0, 0, 255 );
        render_rectangle( rect );
    }

    return 0;
}
