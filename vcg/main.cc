#include <string>
#include <util/log.h>
#include "game.h"

int main( int argc, char *argv[] )
{
	std::string args;
	for ( int i = 0; i < argc; i++ )
		args += argv[ i ];

	log_info( "Arguments: %s", args.c_str() );

	game gm;
	gm.start();

	return 0;
}
