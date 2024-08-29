#include <string>

#include <system/core.h>
#include <util/app.h>
#include <util/log.h>

//#include "ex/raytracer.h"
//#include "ex/gameoflife.h"
//#include "ex/dragon.h"
#include "ex/headless.h"
//#include "main.h"

int main( int argc, char *argv[] )
{
	struct app app;

	std::string args;
	for ( int i = 0; i < argc; i++ )
		args += argv[ i ];

	log_info( "Arguments: %s", args.c_str() );

	core_init( CORE_HEADLESS );
	app_init( &app, init, free, tick, update, render );
	app_loop( &app );
	core_free();

	return 0;
}
