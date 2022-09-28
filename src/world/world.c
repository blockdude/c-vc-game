#include <string.h>
#include "world.h"
#include "../gfx/render.h"
#include "../gfx/window.h"
#include "../input/input.h"

int world_init( struct world *self )
{
    memset( self, 0, sizeof( struct world ) );
    ecs_init( &self->ecs );

    self->camera.x = WORLD_SIZE_X / 2;
    self->camera.y = WORLD_SIZE_Y / 2;
    self->camera.scale = 100.0f;

    for ( int i = 0; i < WORLD_VOLUME; i++ )
    {
        self->chunks[ i ].world = self;
    }

    return 0;
}

int world_free( struct world *self )
{
    memset( self, 0, sizeof( struct world ) );

    return 0;
}

int world_update( struct world *self )
{
    float vx = 0.0f;
    float vy = 0.0f;

    if ( input_key_press( KB_NORTH ) ) vy -= 1.0f;
    if ( input_key_press( KB_SOUTH ) ) vy += 1.0f;
    if ( input_key_press( KB_EAST ) ) vx += 1.0f;
    if ( input_key_press( KB_WEST ) ) vx -= 1.0f;

    normalize( vx, vy, &vx, &vy );
    self->camera.x += vx * 10.0f * window.frame.delta;
    self->camera.y += vy * 10.0f * window.frame.delta;

    return 0;
}

int world_render( struct world *self )
{
    if ( self == NULL )
        return -1;

    for ( int i = 0; i < WORLD_VOLUME; i++ )
    {
        //int z = i / ( WORLD_SIZE_X * WORLD_SIZE_Y );
        int w = i % ( WORLD_SIZE_X * WORLD_SIZE_Y );
        int y = w / WORLD_SIZE_X;
        int x = w % WORLD_SIZE_X;

        int screen_w;
        int screen_h;
        window_get_size( &screen_w, &screen_h );
        int offset_x = screen_w / 2;
        int offset_y = screen_h / 2;

        float rect_x;
        float rect_y;

        rect_x = ( float ) ( ( x - self->camera.x ) * self->camera.scale + offset_x );
        rect_y = ( float ) ( ( y - self->camera.y ) * self->camera.scale + offset_y );

        struct rectangle r = {
            .x = rect_x,
            .y = rect_y,
            .w = self->camera.scale,
            .h = self->camera.scale
        };

        render_set_color( 0, 0, 0, 255 );
        render_rectangle( r );
    }

    return 0;
}
