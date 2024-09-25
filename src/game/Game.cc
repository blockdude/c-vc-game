#include "Game.h"

#include <string>
#include <common.h>

#include "Ship.h"
#include "CelestialBody.h"
#include "Renderer.h"

Game gameLocal;
Game *game = &gameLocal;

//Entity ship;
//CelestialBody planet;

void Game::Init( void )
{
	//ship.Init();
	//planet.Init();
}

void Game::Free( void )
{
}

void Game::Tick( void )
{
	//ship.Tick();
	std::string s =
		"fps: " + std::to_string( FPS() ) + " | "
		"tps: " + std::to_string( TPS() ) + " | "
		"fdt: " + std::to_string( FDELTA() ) + " | "
		"tdt: " + std::to_string( TDELTA() ) + " | ";

	window_title_set( s.c_str() );
}

void Game::Step( void )
{

	//ship.Update();
	//if ( input_keystate( K_W ).pressed )
	//{
	//	ship.move.y += 1.0f;
	//}

	//if ( input_keystate( K_S ).pressed )
	//{
	//	ship.move.y -= 1.0f;
	//}

	//if ( input_keystate( K_A ).pressed )
	//{
	//	ship.move.x += 1.0f;
	//}

	//if ( input_keystate( K_D ).pressed )
	//{
	//	ship.move.x -= 1.0f;
	//}

	//if ( input_keystate( K_E ).pressed )
	//{
	//	ship.rotate += 1.0f;
	//}

	//if ( input_keystate( K_Q ).pressed )
	//{
	//	ship.rotate -= 1.0f;
	//}

	//if ( input_keystate( K_R ).just_pressed )
	//{
	//	ship.Reset();
	//}
}

void Game::Draw( void )
{
	//ship.Draw();
	//planet.Draw();
}
