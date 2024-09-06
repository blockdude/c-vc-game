#include "Game.h"

#include <string>

#include <util/log.h>

#include <graphics/gfx.h>

#include <system/app.h>
#include <system/window.h>
#include <system/input.h>

#include "Ship.h"

#include <system/global.h>

Entity ship;

int init( void )
{
	app_target_fps_set( 144 );
	app_target_tps_set( 100 );
	window_set( WINDOW_VSYNC, false );

	ship.Init();

	return 0;
}

int free( void )
{
	return 0;
}

int tick( void )
{
	ship.Tick();

	std::string s =
        "fps: " + std::to_string( app_fps() ) + " | " +
        "tps: " + std::to_string( app_tps() ) + " | " +
        "dt : " + std::to_string( core.app.state.frame_delta ) + " | ";

	window_title_set( s.c_str() );

	return 0;
}

int update( void )
{
	ship.Update();
	if ( input_key_press( K_W ) )
	{
		ship.move.y += 1.0f;
	}

	if ( input_key_press( K_S ) )
	{
		ship.move.y -= 1.0f;
	}

	if ( input_key_press( K_A ) )
	{
		ship.move.x += 1.0f;
	}

	if ( input_key_press( K_D ) )
	{
		ship.move.x -= 1.0f;
	}

	if ( input_key_press( K_E ) )
	{
		ship.rotate += 1.0f;
	}

	if ( input_key_press( K_Q ) )
	{
		ship.rotate -= 1.0f;
	}

	return 0;
}

int render( void )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	ship.Draw();

    window_swap();
	return 0;
}
