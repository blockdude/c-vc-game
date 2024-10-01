#include "Game.h"

#include <string>
#include <common.h>

#include "Renderer.h"
#include "Player.h"

Game gameLocal;
Game *game = &gameLocal;

static Player player;

void Game::Init( void )
{
	player.Init();
}

void Game::Free( void )
{
}

void Game::Tick( void )
{
	std::string s =
		"fps: " + std::to_string( FPS() ) + " | " +
		"tps: " + std::to_string( TPS() ) + " | " +
		"vel: " + std::to_string( player.velocity.x ) + ":" + std::to_string( player.velocity.y ) + " | " +
		"ang: " + std::to_string( player.angularVelocity );

	window_title_set( s.c_str() );
	player.Tick();
}

void Game::Step( void )
{
	player.Step();
}

void Game::Draw( void )
{
	player.Draw();
}
