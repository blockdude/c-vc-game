#include <string>

#include <system/system.h>
#include <system/app.h>
#include <util/log.h>

#include "Game.h"

int main( int argc, char *argv[] )
{
	std::string args;
	for ( int i = 0; i < argc; i++ )
		args += argv[ i ];

	log_info( "Arguments: %s", args.c_str() );

	sys_init( WINDOW | AUDIO | INPUT | TIMER );
	app_init( init, free, tick, update, render );
	app_loop();
	sys_free();

	return 0;
}
