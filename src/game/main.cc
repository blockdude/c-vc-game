#include <string>
#include <common.h>
#include "Game.h"
#include "Renderer.h"

int main( int argc, char *argv[] )
{
	std::string args;
	for ( int i = 0; i < argc; i++ )
		args += argv[ i ];

	log_info( "Arguments: %s", args.c_str() );

	SETFPS( 0 );
	SETTPS( 100 );

	window_toggle( WINDOW_RELATIVE_MOUSE | WINDOW_RESIZABLE | WINDOW_HIGHDPI );
	sys_init( WINDOW | AUDIO | INPUT | TIMER );

	RendererInit();
	game->Init();

	LOOP()
	{
		TICK()
		{
			game->Tick();
		}

		game->Step();

		RendererColor( BLACK );
		RendererClear();
		RendererColor( WHITE );
		DrawTriangle({
			 1.0f,  1.0f,
			 1.0f, -1.0f,
			-1.0f,  1.0f
		});

		RendererDraw();
	}

	game->Free();
	sys_free();

	return 0;
}
