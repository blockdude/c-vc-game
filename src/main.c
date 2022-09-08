#include "gfx/window.h"
#include "game/game.h"

int main( void )
{
	window_init( &game_init, &game_quit, &game_update, &game_tick, &game_render );
	window_loop();
	window_quit();

	return 0;
}
