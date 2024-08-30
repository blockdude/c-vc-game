#include <string>

#include <util/log.h>
#include <system/system.h>
#include <glad/glad.h>
#include <util/app.h>
#include <cglm/struct.h>
#include <util/list.h>
#include <util/math.h>
#include <util/list.h>
#include <graphics/gfx.h>
#include <system/input.h>
#include <system/window.h>
#include <system/core.h>
#include <system/core-internal.h>

static const float square[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,

     1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f
};

static const float cube[] = {
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,

     1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,



     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,



    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,



    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,

     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,



     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,

     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,



     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,

     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

static struct camera camera;
static struct shader shader;
static struct vao vao;
static struct vbo vbo;

static int init( struct app *app )
{
	( void )app;
	app_target_fps_set( app, 144 );
	app_target_tps_set( app, 30 );
	window_relative_mouse( true );

	glEnable( GL_DEPTH_TEST );

	if ( shader_loadf( &shader, "res/shaders/2d.vert", "res/shaders/2d.frag" ) != 0 )
		exit( 1 );

	shader_bind( shader );

	vao = vao_create();
	vao_bind( vao );
	vbo = vbo_create( GL_ARRAY_BUFFER, false );
	vbo_bind( vbo );
	vbo_buff( vbo, ( void * ) cube, sizeof( cube ) );
	int position_i = glGetAttribLocation( shader.handle, "position" );
	vao_attr( vao, vbo, position_i, 3, GL_FLOAT, 0, 0 );

	camera_init( &camera, DEGTORAD( 45 ) );
	camera.eye.x = 0;
	camera.eye.y = 0;
	camera.eye.z = 0;
	camera.pitch = DEGTORAD( 0 );
	camera.yaw = DEGTORAD( 0 );

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

	std::string s =
        std::to_string( app->frame_rate ) + " | " +
        std::to_string( app->frame_avg ) + " | " +
        std::to_string( app->frame_delta ) + " | " +
        std::to_string( app->frame_target ) + " | " +
        std::to_string( app->frame_count );

	window_set_title( s.c_str() );

	return 0;
}

static int update( struct app *app )
{
	( void ) app;

    vec3_t direction = vec3_zero();
    if ( input_key_press( KB_W ) )
    {
        direction.x += sinf( camera.yaw );
        direction.z += cosf( camera.yaw );
    }

    if ( input_key_press( KB_S ) )
    {
        direction.x -= sinf( camera.yaw );
        direction.z -= cosf( camera.yaw );
    }

    if ( input_key_press( KB_A ) )
    {
        direction.x += cosf( camera.yaw );
        direction.z -= sinf( camera.yaw );
    }

    if ( input_key_press( KB_D ) )
    {
        direction.x -= cosf( camera.yaw );
        direction.z += sinf( camera.yaw );
    }

    if ( input_key_press( KB_SPACE ) )
    {
        direction.y += 1;
    }

    if ( input_key_press( KB_LSHIFT ) )
    {
        direction.y -= 1;
    }

    if ( input_mouse_moved() )
    {
        vec2_t d = input_mouse_delta();
        camera.yaw   -= d.x * 0.0009f;
        camera.pitch -= d.y * 0.0009f;
    }

    if ( input_key_down( KB_ESCAPE ) )
    {
        window_relative_mouse_toggle();
    }

    direction = vec3_normalize( direction );
    direction = vec3_scale( direction, 10.0f * app->frame_delta );
    camera.eye = vec3_add( camera.eye, direction );
    camera.aspect = core.window.aspect;

	mat4_t model_matrix = mat4_identity();

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

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glDrawArrays( GL_TRIANGLES, 0, 36 );

    window_swap();

	return 0;
}
