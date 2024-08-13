#include "SDL3/SDL_video.h"
#include "gfx/camera.h"
#include "gfx/vbo.h"
#include "system/input.h"
#include <string>

#include <util/log.h>
#include <system/system.h>
#include <glad/glad.h>
#include <system/app.h>
#include <cglm/struct.h>
#include <util/list.h>
#include <util/fmath.h>
#include <util/list.h>
#include <gfx/gfx.h>

static struct camera camera;
static struct obj3d dragon;
static struct shader shader;
static struct vao vao;
static struct vbo vbo;

static int init( struct app *app )
{
	( void )app;
	system_init();
	window_init();
	app_set_target_fps( app, 0 );
	SDL_GL_SetSwapInterval( 0 );

	glEnable( GL_DEPTH_TEST );

	if ( obj3d_load( &dragon, "res/objects/dragon.obj" ) != 0 )
	{
		exit( 1 );
	}

	if ( shader_fbuild( &shader, "res/shaders/vert.glsl", "res/shaders/frag.glsl" ) != 0 )
	{
		exit( 1 );
	}

	shader_bind( shader );

	vao = vao_create();
	vao_bind( vao );

	vbo = vbo_create( GL_ARRAY_BUFFER, false );
	vbo_bind( vbo );

	vbo_buff( vbo, dragon.fv, dragon.fv_nbytes );

	GLuint pos_loc = glGetAttribLocation( shader.handle, "position" );
	GLuint norm_loc = glGetAttribLocation( shader.handle, "normal" );

	vao_attr(
		vao, vbo,
		pos_loc,
		dragon.vp_nval,
		GL_FLOAT,
		dragon.stride,
		dragon.vp_offset
	);

	vao_attr(
		vao, vbo,
		norm_loc,
		dragon.vn_nval,
		GL_FLOAT,
		dragon.stride,
		dragon.vn_offset
	);

	camera_init( &camera, degtorad( 90 ) );
	camera.eye[ 0 ] = dragon.center.raw[ 0 ];
	camera.eye[ 1 ] = dragon.center.raw[ 1 ];
	camera.eye[ 2 ] = dragon.center.raw[ 2 ] + dragon.dia;
	camera.pitch = degtorad( 0 );
	camera.yaw = degtorad( 180 );

	return 0;
}

static int free( struct app *app )
{
	( void )app;
	obj3d_free( &dragon );
	window_free();
	system_free();
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

	mat4 model_matrix = {
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};

	camera_update( &camera );
	shader_uniform_mat4( shader, "view_matrix", camera.view );
	shader_uniform_mat4( shader, "proj_matrix", camera.proj );
	shader_uniform_mat4( shader, "model_matrix", model_matrix );

	return 0;
}

static int render( struct app *app )
{
	( void )app;
	glClearColor( 1.f, 1.f, 1.f, 1.f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glDrawArrays(
		GL_TRIANGLES,
		0,
		dragon.fv_len
	);

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
