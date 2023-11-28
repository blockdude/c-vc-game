#include "game.h"
#include "state.h"
#include <gfx/window.h>
#include <gfx/render.h>
#include <util/util.h>
#include <system/input.h>
#include <glad/glad.h>

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
    glClearColor( 1.f, 1.f, 1.f, 1.f );
    glClear( GL_COLOR_BUFFER_BIT );

    char buff[ 256 ];
    sprintf( buff, "frame : %5lu | fps : %u | tick : %5lu | tps : %u", window.frame.count, window.frame.rate, window.tick.count, window.tick.rate );
    window_set_title( buff );

    return 0;
}
