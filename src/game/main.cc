#include <string>

#include <util/log.h>
#include <gfx/window.h>
#include <system/system.h>
#include <glad/glad.h>
#include <system/app.h>
#include <cglm/struct.h>
#include <util/list.h>

static int init( struct app *app )
{
	( void )app;
	system_init();
	window_init();
	app_set_target_fps( app, 0 );
	//SDL_GL_SetSwapInterval( 0 );

	return 0;
}

static int free( struct app *app )
{
	( void )app;
	window_free();
	system_free();
	return 0;
}

static int tick( struct app *app )
{
	( void )app;
	return 0;
}

static int update( struct app *app )
{
	( void )app;
	std::string s = std::to_string( app->frame_rate ) + " | " + std::to_string( app->tick_rate );
	window_set_title( s.c_str() );
	return 0;
}

static int render( struct app *app )
{
	( void )app;
	glClearColor( 1.f, 1.f, 1.f, 1.f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	SDL_GL_SwapWindow( window.handle );
	return 0;
}

int main( int argc, char *argv[] )
{
	std::string args;
	for ( int i = 0; i < argc; i++ )
		args += argv[ i ];

	log_info( "Arguments: %s", args.c_str() );

	struct app app;
	app_init( &app, {
		.init   = init,
		.free   = free,
		.tick   = tick,
		.update = update,
		.render = render
	});

	app_loop( &app );

	return 0;
}
