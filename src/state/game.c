#include "game.h"
#include "state.h"
#include "../gfx/window.h"
#include "../gfx/render.h"
#include "../util/util.h"
#include "../system/input.h"

int game_init( void )
{
    return 0;
}

int game_free( void )
{
    return 0;
}

int game_tick( void )
{
    return 0;
}

int game_update( void )
{
    return 0;
}

int game_render( void )
{
    render_set_color( 255, 255, 255, 255 );
    render_clear();
    render_present();

    char buff[ 256 ];
    sprintf( buff, "frame : %5lu | fps : %u | tick : %5lu | tps : %u", window.frame.count, window.frame.rate, window.tick.count, window.tick.rate );
    window_set_title( buff );

    return 0;
}
