#include <gfx/window.h>
#include <system/system.h>
#include <glad/glad.h>
#include <state/app.h>
#include <cglm/struct.h>

#include "game.h"
#include <vector>
#include <iostream>
#include <string>

static struct app app;
static std::vector< game * > games;

static int init_( void )
{
	// setup
	system_init();
	window_init();
	//SDL_GL_SetSwapInterval( 0 );
	app_set_target_fps( &app, 0 );
	for ( game *g : games ) g->init();

	return 0;
}

static int free_( void )
{
	// free memory
	window_free();
	system_free();
	for ( game *g : games ) g->free();
	return 0;
}

static int tick_( void )
{
	return 0;
}

static int update_( void )
{
	std::string s = std::to_string( app.frame_rate ) + " | " + std::to_string( app.tick_rate );
	window_set_title( s.c_str() );
	for ( game *g : games ) g->update();
	return 0;
}

static int render_( void )
{
	glClearColor( 1.f, 1.f, 1.f, 1.f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	for ( game *g : games ) g->render();
	SDL_GL_SwapWindow( window.handle );
	return 0;
}

game::game( void )
{
	games.push_back( this );
}

void game::start( void )
{
	app_init( &app, {
		.init   = init_,
		.free   = free_,
		.tick   = tick_,
		.update = update_,
		.render = render_
	});

	app_loop( &app );
}

int game::init( void )
{
	return 0;
}

int game::free( void )
{
	return 0;
}

int game::tick( void )
{
	return 0;
}

int game::update( void )
{
	return 0;
}

int game::render( void )
{
	return 0;
}
