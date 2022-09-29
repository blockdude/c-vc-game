#include <string.h>
#include "gen/generate.h"
#include "world.h"
#include "../gfx/render.h"
#include "../gfx/window.h"
#include "../input/input.h"

int world_init( struct world *self, size_t world_size_x, size_t world_size_y, size_t world_size_z )
{
    memset( self, 0, sizeof( struct world ) );
    ecs_init( &self->ecs );

    self->world_size_x = world_size_x;
    self->world_size_y = world_size_y;
    self->world_size_z = world_size_z;
    self->chunks_count = world_size_x * world_size_y * world_size_z;
    self->chunks = calloc( self->chunks_count, sizeof( *self->chunks ) );

    for ( size_t i = 0; i < self->chunks_count; i++ )
    {
        chunk_init( &self->chunks[ i ], self, i );
        generate_chunk( &self->chunks[ i ] );
    }

    self->camera.x = 0.0f;//self->world_size_x * CHUNK_SIZE_X / 2;
    self->camera.y = 0.0f;//self->world_size_y * CHUNK_SIZE_Y / 2;
    self->camera.scale = 5.0f;

    return 0;
}

int world_free( struct world *self )
{
    ecs_free( &self->ecs );

    for ( size_t i = 0; i < self->chunks_count; i++ )
        chunk_free( &self->chunks[ i ] );

    free( self->chunks );
    memset( self, 0, sizeof( struct world ) );

    return 0;
}

int world_update( struct world *self )
{
    if ( self == NULL )
        return -1;

    if ( input_key_press( KB_UP ) ) self->camera.scale += 10.0f * window.frame.delta;
    if ( input_key_press( KB_DOWN ) ) self->camera.scale -= 10.0f * window.frame.delta;
            
    return 0;
}

int world_tick( struct world *self )
{
    if ( self == NULL )
        return -1;

    self->tick++;

    return 0;
}

int world_render( struct world *self )
{
    if ( self == NULL )
        return -1;

    int screen_w;
    int screen_h;
    window_get_size( &screen_w, &screen_h );
    int screen_center_x = screen_w / 2;
    int screen_center_y = screen_h / 2;

    float m[] = {
        -1.0f, -1.0f,
        -1.0f, 0.0f,
        -1.0f, 1.0f,

        0.0f, -1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,

        1.0f, -1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
    };

    printf( "|------------------|------------|--------|--------------|\n" );
    printf( "|camera_pos        |chunk_pos   |index   |count         |\n" );
    printf( "|------------------|------------|--------|--------------|\n" );

    for ( int i = 0; i < 9; i++ )
    {
        // get xyz index
        int y = floor( self->camera.y / CHUNK_SIZE_Y ) + m[ i * 2 ];
        int x = floor( self->camera.x / CHUNK_SIZE_X ) + m[ i * 2 + 1 ];
        // replace to get player chunk z coordinates
        int z = 0;

        // convert xyz into an index for world chunk array
        int idx = ( z * self->world_size_x * self->world_size_y ) + ( y * self->world_size_x ) + x;
        printf( "| %7.2f, %7.2f | %4d, %4d | %6d | %12ld |", self->camera.x + m[ i * 2 ], self->camera.y + m[ i * 2 + 1 ], x, y, idx, self->chunks_count );

        // stop if out of bounds in array
        if ( x < 0 || y < 0 || x >= ( int ) self->world_size_x || y >= ( int ) self->world_size_y )
        {
            printf( "\n" );
            continue;
        }

        // convert xy into screen coordinates
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
        render_set_color( 255, 0, 0, 255 );
        render_rectangle( rect );
    }

    // draw cross hair

    render_set_color( 0, 0, 0, 255 );

    struct line line_a = {
        .x0 = screen_center_x - 10,
        .y0 = screen_center_y,
        .x1 = screen_center_x + 10,
        .y1 = screen_center_y
    };

    struct line line_b = {
        .x0 = screen_center_x,
        .y0 = screen_center_y - 10,
        .x1 = screen_center_x,
        .y1 = screen_center_y + 10
    };

    render_line( line_a );
    render_line( line_b );

    return 0;
}
