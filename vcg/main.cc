#include <gfx/window.h>
#include <gfx/render.h>
#include <system/system.h>
#include <glad/glad.h>
#include <state/stage.h>
#include <iostream>
#include <string>

namespace app
{

int init( struct game *gm )
{
	// setup
	system_init();
	window_init();
	render_init();
	( void )gm;

	return 0;
}

int free( struct game *gm )
{
	// free memory
	render_free();
	window_free();
	system_free();
	( void )gm;
	return 0;
}

int tick( struct game *gm )
{
	( void )gm;
	return 0;
}

int update( struct game *gm )
{
	std::string s = std::to_string( gm->frame_delta );
	window_set_title( s.c_str() );
	return 0;
}

int render( struct game *gm )
{
	( void )gm;
	glClearColor( 1.f, 1.f, 1.f, 1.f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	SDL_GL_SwapWindow( window.handle );
	return 0;
}

};

int main( int argc, char *argv[] )
{
	// store arguments in a buffer
	const int buf_size = 256;
	char buf[ buf_size ];
	int buf_pos = 0;
	for ( int i = 0; i < argc; i++ )
		buf_pos += snprintf( buf + buf_pos, buf_size - buf_pos, "%s ", argv[ i ] );

	// log arguments
	log_info( "Arguments: %s", buf );

	struct stage s = {
		.init = app::init,
		.free = app::free,
		.tick = app::tick,
		.update = app::update,
		.render = app::render
	};

	struct game gm;
	game_init( &gm, &s );
	game_start( &gm );

	return 0;
}
