#include "Game.h"

#include <string>
#include <lib.h>

#include "Ship.h"
#include "CelestialBody.h"

Game gameLocal;
Game *game = &gameLocal;

Entity ship;
CelestialBody planet;

void Game::Init( void )
{
	ship.Init();
	planet.Init();
}

void Game::Free( void )
{
}

void Game::Tick( void )
{
	ship.Tick();
}

void Game::Step( void )
{
	std::string s =
		"fps: " + std::to_string( FPS() ) + " | "
		"tps: " + std::to_string( TPS() ) + " | "
		"fdt: " + std::to_string( FDELTA() ) + " | "
		"tdt: " + std::to_string( TDELTA() ) + " | ";

	window_title_set( s.c_str() );

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

	if ( input_key_down( K_R ) )
	{
		ship.Reset();
	}
}

void Game::Draw( void )
{
	ship.Draw();
	planet.Draw();
}
