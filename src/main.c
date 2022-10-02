#include "gfx/window.h"
#include "gfx/render.h"
#include "state/state.h"

int main( void )
{
	window_init( &game_state );
	render_init();

	window_start();

	render_free();
	window_close();

	return 0;
}
