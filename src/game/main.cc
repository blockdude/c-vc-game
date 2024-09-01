#include <string>

#include <system/core.h>
#include <system/app.h>
#include <util/log.h>

//#include "ex/raytracer.h"
//#include "ex/gameoflife.h"
//#include "ex/dragon.h"
//#include "ex/headless.h"
//#include "ex/cube.h"
//#include "ex/terrain.h"
#include "game.h"

int main( int argc, char *argv[] )
{
	std::string args;
	for ( int i = 0; i < argc; i++ )
		args += argv[ i ];

	log_info( "Arguments: %s", args.c_str() );

	core_init( WINDOW | AUDIO | INPUT | TIMER );
	app_init( init, free, tick, update, render );
	app_loop( );
	core_free();

	return 0;
}
