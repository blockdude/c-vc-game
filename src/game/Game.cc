#include "Game.h"

#include <string>
#include <common.h>

Game gameLocal;
Game *game = &gameLocal;

void Game::Init( void )
{
}

void Game::Free( void )
{
}

void Game::Tick( void )
{
	std::string s =
		"fps: " + std::to_string( FPS() ) + " | "
		"tps: " + std::to_string( TPS() ) + " | ";

	window_title_set( s.c_str() );
}

void Game::Step( void )
{
}

void Game::Draw( void )
{
}
