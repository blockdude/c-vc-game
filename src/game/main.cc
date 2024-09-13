#include <string>
#include <common.h>
#include "Game.h"

int main( int argc, char *argv[] )
{
	std::string args;
	for ( int i = 0; i < argc; i++ )
		args += argv[ i ];

	log_info( "Arguments: %s", args.c_str() );

	SETFPS( 144 );
	SETTPS( 100 );
	window_set( WINDOW_VSYNC | WINDOW_RELATIVE_MOUSE, true );

	sys_init( WINDOW | AUDIO | INPUT | TIMER );
	game->Init();

	LOOP()
	{
		TICK()
		{
			game->Tick();
		}

		game->Step();
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		game->Draw();
		window_swap();
	}

	game->Free();
	sys_free();

	return 0;
}
