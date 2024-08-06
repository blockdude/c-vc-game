#include <gfx/window.h>
#include <system/system.h>
#include <glad/glad.h>
#include <state/app.h>

#include <string>

namespace game
{

struct app app;

int init( struct app *app )
{
	// setup
	system_init();
	window_init();
	( void )app;

	return 0;
}

int free( struct app *app )
{
	// free memory
	window_free();
	system_free();
	( void )app;
	return 0;
}

int tick( struct app *app )
{
	( void )app;
	return 0;
}

int update( struct app *app )
{
	std::string s = std::to_string( app->frame_count ) + " | " + std::to_string( app->tick_count );
	window_set_title( s.c_str() );
	return 0;
}

int render( struct app *app )
{
	( void )app;
	glClearColor( 1.f, 1.f, 1.f, 1.f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	SDL_GL_SwapWindow( window.handle );
	return 0;
}

void start( void )
{
	app_init( &app, {
		.init   = init,
		.free   = free,
		.tick   = tick,
		.update = update,
		.render = render
	});

	app_loop( &app );
}

};

int main( int argc, char *argv[] )
{
	std::string args;
	for ( int i = 0; i < argc; i++ )
		args += argv[ i ];

	log_info( "Arguments: %s", args.c_str() );

	game::start();
	return 0;
}
