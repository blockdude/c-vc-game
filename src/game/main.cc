#include <string>

#include <system/system.h>
#include <system/app.h>
#include <util/log.h>
#include <gfx/gfx.h>

#include "ex/raytracer.h"
//#include "ex/gameoflife.h"
//#include "ex/dragon.h"
//#include "main.h"

int main( int argc, char *argv[] )
{
	std::string args;
	for ( int i = 0; i < argc; i++ )
		args += argv[ i ];

	log_info( "Arguments: %s", args.c_str() );

	system_init();
	window_init();

	struct app app;
	app_init( &app,
		init,
		free,
		tick,
		update,
		render
	);

	app_loop( &app );

	window_free();
	system_free();

	return 0;
}
