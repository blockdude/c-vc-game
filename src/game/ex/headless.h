#include <string>

#include <util/log.h>
#include <util/app.h>
#include <system/input.h>

static int init( struct app *app )
{
	( void )app;
	app_set_target_fps( app, 60 );
	app_set_target_tps( app, 3 );
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
