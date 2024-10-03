#include <string>

#include <util/log.h>
#include <util/app.h>
#include <system/input.h>

static int init( struct app *app )
{
	( void )app;
	app_target_fps_set( app, 60 );
	app_target_tps_set( app, 3 );
	return 0;
}

static int free( struct app *app )
{
	( void )app;
	return 0;
}

static int tick( struct app *app )
{
	( void )app;
	std::string s = std::to_string( app->frame_avg ) + " | " + std::to_string( app->tick_avg );
	log_debug( s.c_str() );
	return 0;
}

static int update( struct app *app )
{
	( void )app;
	return 0;
}

static int render( struct app *app )
{
	( void )app;
	return 0;
}
