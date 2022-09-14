#include "gfx/window.h"
#include "state/game.h"

int main( void )
{
	// starting game state
	struct window_state state = {
		.init		= &game_init,
		.free		= &game_free,
		.update 	= &game_update,
		.tick		= &game_tick,
		.render 	= &game_render
	};

	window_init( &state );
	window_start();
	window_close();

	return 0;
}
