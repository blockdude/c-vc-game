#include "game.h"
#include "../gfx/window.h"
#include "../gfx/render.h"
#include "../util/util.h"
#include "../world/world.h"
#include "../input/input.h"

// new world
static struct world world;

int game_init( void )
{
    tile_init();
    world_init( &world, 16, 16, 16 );
    return 0;
}

int game_free( void )
{
    world_free( &world );
	return 0;
}

int game_update( void )
{
    world_update( &world );

    float vx = 0.0f;
    float vy = 0.0f;

    if ( input_key_press( KB_NORTH ) ) vy -= 1.0f;
    if ( input_key_press( KB_SOUTH ) ) vy += 1.0f;
    if ( input_key_press( KB_EAST ) ) vx += 1.0f;
    if ( input_key_press( KB_WEST ) ) vx -= 1.0f;

    normalize( vx, vy, &vx, &vy );
    world.camera.x += vx * 5.0f * window.frame.delta;
    world.camera.y += vy * 5.0f * window.frame.delta;

    return 0;
}

int game_tick( void )
{
    world_tick( &world );
    return 0;
}

int game_render( void )
{
	render_set_color( 255, 255, 255, 255 );
	render_clear();

    printf( "|-------------|-------------|\n" );
    printf( "|frame: %5lu |tick : %5lu |\n", window.frame.count, window.tick.count );
    printf( "|fps  : %5u |tps  : %5u |\n", window.frame.rate, window.tick.rate );
    world_render( &world );

	render_present();

    return 0;
}
