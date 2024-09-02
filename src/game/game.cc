#include "game.h"

#include <string>

#include <util/log.h>

#include <graphics/gfx.h>

#include <system/app.h>
#include <system/window.h>
#include <system/input.h>

#include "ship.h"

Entity ship;

int init( void )
{
	app_target_fps_set( 144 );
	app_target_tps_set( 100 );

	ship.Init();

	return 0;
}

int free( void )
{
	return 0;
}

int tick( void )
{
	std::string s =
        "fps: " + std::to_string( app_fps() ) + " | " +
        "tps: " + std::to_string( app_tps() ) + " | ";

	window_title_set( s.c_str() );

	ship.Tick();
	log_debug( "%f", vec3_len( ship.velocity ) );

	return 0;
}

int update( void )
{
	ship.Update();
	if ( input_key_press( KB_W ) )
	{
		ship.direction.y += 1.0f;
	}

	if ( input_key_press( KB_S ) )
	{
		ship.direction.y -= 1.0f;
	}

	if ( input_key_press( KB_A ) )
	{
		ship.direction.x += 1.0f;
	}

	if ( input_key_press( KB_D ) )
	{
		ship.direction.x -= 1.0f;
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
