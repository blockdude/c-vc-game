#include "world.h"
#include "../gfx/draw.h"
#include "../gfx/window.h"
#include <assert.h>

int world_init( struct world *self )
{
    *self = ( struct world ) { 0 };
    ecs_init( &self->ecs );

	return 0;
}

int world_free( struct world *self )
{
    *self = ( struct world ) { 0 };

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

        rect_x = ( float ) ( ( x - self->camera.x ) * 100.0f + offset_x );
        rect_y = ( float ) ( ( y - self->camera.y ) * 100.0f + offset_y );

        struct rectangle r = {
            .x = rect_x,
            .y = rect_y,
            .w = 100.0f,
            .h = 100.0f
        };

        render_set_color( 0, 0, 0, 255 );
        draw_rectangle( r );
    }

    return 0;
}
