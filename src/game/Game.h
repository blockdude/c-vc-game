#ifndef GM_H
#define GM_H

#include <string>

#include <util/log.h>

#include <graphics/gfx.h>

#include <system/timestep.h>
#include <system/window.h>
#include <system/input.h>

#include "Ship.h"

static Entity ship;

class GameManager
{
public:
	void Init( void )
	{
		SETFPS( 144 );
		SETTPS( 100 );
		window_set( WINDOW_VSYNC, false );

		ship.Init();
	}

	void Free( void )
	{
	}

	void Tick( void )
	{
		ship.Tick();

	}

	void Update( void )
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

		std::string s =
			"fps: " + std::to_string( FPS() ) + " | "
			"fps: " + std::to_string( TPS() ) + " | "
			"fps: " + std::to_string( __loop.t_delta ) + " | ";

		window_title_set( s.c_str() );
	}

	void Render( void )
	{
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		ship.Draw();

		window_swap();
	}

	void Run( void )
	{
		Init();

		LOOP()
		{
			TICK()
			{
				Tick();
			}

			Update();
			Render();
		}

		Free();
	}
};

#endif
