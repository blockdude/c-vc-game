#include <string>

#include <util/log.h>
#include <system/system.h>
#include <glad/glad.h>
#include <system/app.h>
#include <cglm/struct.h>
#include <util/list.h>
#include <util/math.h>
#include <util/list.h>
#include <gfx/gfx.h>

static const GLfloat square[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
     1.0f,  1.0f,

     1.0f,  1.0f,
    -1.0f,  1.0f,
    -1.0f, -1.0f
};

static struct camera camera;
static struct shader shader;
static struct vao vao;
static struct vbo vbo;
static int state_idx;

static int init( struct app *app )
{
	( void )app;
	app_set_target_fps( app, 0 );
	app_set_target_tps( app, 30 );
	SDL_GL_SetSwapInterval( 0 );

	glEnable( GL_DEPTH_TEST );

	if ( shader_loadf( &shader, "res/shaders/instancing.vert", "res/shaders/simple.frag" ) != 0 )
		exit( 1 );

	shader_bind( shader );
	state_idx = glGetUniformLocation( shader.handle, "state" );


	vao = vao_create();
	vao_bind( vao );
	vbo = vbo_create( GL_ARRAY_BUFFER, false );
	vbo_bind( vbo );
	vbo_buff( vbo, ( void * ) square, sizeof( square ) );
	int position_i = glGetAttribLocation( shader.handle, "position" );
	vao_attr( vao, vbo, position_i, 2, GL_FLOAT, 0, 0 );

	return 0;
}

static int free( struct app *app )
{
	( void )app;
	vbo_free( vbo );
	vao_free( vao );
	shader_free( shader );
	return 0;
}

static int tick( struct app *app )
{
	( void )app;

	std::string s = std::to_string( app->frame_rate ) + " | " + std::to_string( app->tick_rate );
	window_set_title( s.c_str() );

	return 0;
}

static int update( struct app *app )
{
	( void ) app;

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
