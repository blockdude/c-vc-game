#include "gfx/window.h"
#include "gfx/render.h"
#include "state/state.h"

int main( int argc, char *argv[] )
{
	// print arguments
	for ( int i = 0; i < argc; i++ )
		printf( "%s ", argv[ i ] );
	printf( "\n" );

	// setup
	window_init( &game_state );
	render_init();

	// loop
	window_start();

	// free memory
	render_free();
	window_close();

	return 0;
}
