#include "game.h"
#include "../gfx/window.h"
#include "../gfx/render.h"
#include "../util/util.h"

int game_init( void )
{
	render_init();
    return 0;
}

int game_free( void )
{
	render_free();
    return 0;
}

int game_update( void )
{
    return 0;
}

int game_tick( void )
{
    return 0;
}

int game_render( void )
{
	render_set_color( 255, 255, 255, 255 );
	render_clear();
	render_present();

    printf( "---------------------------\n" );
    printf( "frame: %lu\ttick: %lu\n", window.frame.count, window.tick.count );
    printf( "fps  : %u\ttps : %u\n", window.frame.rate, window.tick.rate );

    return 0;
}
