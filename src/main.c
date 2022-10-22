#include "gfx/window.h"
#include "gfx/render.h"
#include "state/state.h"
#include "util/util.h"

int main( int argc, char *argv[] )
{
	// store arguments in a buffer
	int buf_size = 256;
	char buf[ buf_size ];
	int buf_pos = 0;
	for ( int i = 0; i < argc; i++ )
		buf_pos += snprintf( buf + buf_pos, buf_size - buf_pos, "%s ", argv[ i ] );

	// log arguments
	log_info( "executed with: %s", buf );

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
