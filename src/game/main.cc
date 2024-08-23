#include <string>

#include <system/system.h>
#include <system/app.h>

//#include "raytracer.h"
#include "gameoflife.h"

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
		.init   = init,
		.free   = free,
		.tick   = tick,
		.update = update,
		.render = render
	});

	app_loop( &app );

	window_free();
	system_free();

	return 0;
}
