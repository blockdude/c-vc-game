#include "game.h"
#include "state.h"
#include "../gfx/window.h"
#include "../gfx/render.h"
#include "../util/util.h"
#include "../world/world.h"
#include "../system/input.h"
#include "../world/gen/gen.h"

int game_init( void )
{
    tile_init();
    world_init( &state.world, 16, 16, 8 );
    gen_world( &state.world );

    return 0;
}

int game_free( void )
{
    world_free( &state.world );
    return 0;
}

int game_tick( void )
{
    world_tick( &state.world );
    return 0;
}

int game_update( void )
{
    world_update( &state.world );

    float vx = 0.0f;
    float vy = 0.0f;
    float scroll_delta = 0.0f;
    float scroll_speed = 1.1f;
    float player_speed = 10.0f;

    // get input
    // if ( input_key_press( KB_NORTH ) ) vy -= 1.0f;
    // if ( input_key_press( KB_SOUTH ) ) vy += 1.0f;
    // if ( input_key_press( KB_EAST ) ) vx += 1.0f;
    // if ( input_key_press( KB_WEST ) ) vx -= 1.0f;
    scroll_delta = input_mouse_scroll();

    // apply input
    normalize( vx, vy, &vx, &vy );
    state.world.camera.x += vx * player_speed * window.frame.delta;
    state.world.camera.y += vy * player_speed * window.frame.delta;

    state.world.camera.scale *= scroll_delta != 0 ? pow( scroll_speed, scroll_delta ) : 1.0f;

    return 0;
}

int game_render( void )
{
    render_set_color( 255, 255, 255, 255 );
    render_clear();

    // get screen center
    int screen_center_x;
    int screen_center_y;

    window_get_size( &screen_center_x, &screen_center_y );

    screen_center_x = screen_center_x / 2;
    screen_center_y = screen_center_y / 2;

    world_render( &state.world );

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

    render_present();

    char buff[ 256 ];
    sprintf( buff, "frame : %5lu | fps : %u | tick : %5lu | tps : %u", window.frame.count, window.frame.rate, window.frame.count, window.tick.rate );
    window_set_title( buff );

    return 0;
}
