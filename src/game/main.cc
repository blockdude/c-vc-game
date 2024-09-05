#include <string>

#include <system/core.h>
#include <system/app.h>
#include <util/log.h>

#include "Game.h"

#include <tinyobj_loader_c.h>

int main( int argc, char *argv[] )
{
	std::string args;
	for ( int i = 0; i < argc; i++ )
		args += argv[ i ];

	log_info( "Arguments: %s", args.c_str() );

	core_init( WINDOW | AUDIO | INPUT | TIMER );
	app_init( init, free, tick, update, render );
	app_loop();
	core_free();

	return 0;
}
