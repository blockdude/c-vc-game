#include "gfx/window.h"
#include "gfx/render.h"
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
	render_init();

	window_start();

	render_free();
	window_close();

	return 0;
}
