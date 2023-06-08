#include "gfx/window.h"
#include "gfx/render.h"
#include "system/system.h"
#include "state/state.h"

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
	system_init();
	window_init( &state.game );
	render_init();

	// loop
	window_loop();

	// free memory
	render_free();
	window_free();
	system_free();

	return 0;
}
