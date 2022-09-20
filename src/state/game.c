#include "game.h"
#include "../gfx/window.h"
#include "../gfx/render.h"
#include "../util/util.h"
#include "../world/world.h"

// new world
static struct world world;

int game_init( void )
{
    world_init( &world );
    return 0;
}

int game_free( void )
{
    world_free( &world );
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

    world_render( &world );

	render_present();

    printf( "---------------------------\n" );
    printf( "frame: %lu\ttick: %lu\n", window.frame.count, window.tick.count );
    printf( "fps  : %u\ttps : %u\n", window.frame.rate, window.tick.rate );

    return 0;
}
