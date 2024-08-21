#include <string>

#include <system/system.h>
#include <system/app.h>

#include "raytracer.h"

int main( int argc, char *argv[] )
{
	std::string args;
	for ( int i = 0; i < argc; i++ )
		args += argv[ i ];

	log_info( "Arguments: %s", args.c_str() );

	system_init();
	window_init();

	struct app app;
	app_init( &app, {
		.init   = game_init,
		.free   = game_free,
		.tick   = game_tick,
		.update = game_update,
		.render = game_render
	});

	app_loop( &app );

	window_free();
	system_free();

	return 0;
}
