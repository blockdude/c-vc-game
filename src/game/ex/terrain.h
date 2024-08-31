#include <string>

#include <util/log.h>
#include <util/app.h>
#include <util/list.h>
#include <util/math.h>
#include <util/list.h>
#include <util/camera.h>

#include <graphics/gfx.h>

#include <system/core.h>
#include <system/window.h>
#include <system/input.h>

static float *terrain = NULL;
static struct camera camera;
static struct shader shader;
static struct vao vao;
static struct vbo vbo;

static int point_count( void )
{
    return list_size( terrain ) / 6;
}

static void terrain_init( int s )
{
    for ( int x = 0; x < s; x++ )
    {
        for ( int y = 0; y < s; y++ )
        {
            vec3_t color = { 0.0f, 0.0f, 0.0f };

            vec3_t v0 = { ( float ) x,        0.0f, ( float ) y        };
            vec3_t v1 = { ( float ) x + 1.0f, 0.0f, ( float ) y        };
            vec3_t v2 = { ( float ) x       , 0.0f, ( float ) y + 1.0f };

            vec3_t v3 = { ( float ) x + 1.0f, 0.0f, ( float ) y        };
            vec3_t v4 = { ( float ) x + 1.0f, 0.0f, ( float ) y + 1.0f };
            vec3_t v5 = { ( float ) x       , 0.0f, ( float ) y + 1.0f };

            list_push_back( terrain, v0.x );
            list_push_back( terrain, v0.y );
            list_push_back( terrain, v0.z );

            list_push_back( terrain, color.x );
            list_push_back( terrain, color.y );
            list_push_back( terrain, color.z );

            list_push_back( terrain, v1.x );
            list_push_back( terrain, v1.y );
            list_push_back( terrain, v1.z );

            list_push_back( terrain, color.x );
            list_push_back( terrain, color.y );
            list_push_back( terrain, color.z );

            list_push_back( terrain, v2.x );
            list_push_back( terrain, v2.y );
            list_push_back( terrain, v2.z );

            list_push_back( terrain, color.x );
            list_push_back( terrain, color.y );
            list_push_back( terrain, color.z );

            list_push_back( terrain, v3.x );
            list_push_back( terrain, v3.y );
            list_push_back( terrain, v3.z );

            list_push_back( terrain, color.x );
            list_push_back( terrain, color.y );
            list_push_back( terrain, color.z );

            list_push_back( terrain, v4.x );
            list_push_back( terrain, v4.y );
            list_push_back( terrain, v4.z );

            list_push_back( terrain, color.x );
            list_push_back( terrain, color.y );
            list_push_back( terrain, color.z );

            list_push_back( terrain, v5.x );
            list_push_back( terrain, v5.y );
            list_push_back( terrain, v5.z );

            list_push_back( terrain, color.x );
            list_push_back( terrain, color.y );
            list_push_back( terrain, color.z );
        }
    }
}

static void terrain_rand( void )
{
    int s = point_count();
    for ( int i = 0; i < s; i++ )
    {
        int xi = i * 6 + 0;
        int yi = i * 6 + 1;
        int zi = i * 6 + 2;

        int ri = i * 6 + 3;
        int gi = i * 6 + 4;
        int bi = i * 6 + 5;

        float x = terrain[ xi ];
        float y = terrain[ yi ];
        float z = terrain[ zi ];

        //float w = 20.0f;
        //float v = 5.0f;
        //float contour = ( sinf( x / w ) + cosf( z / w ) ) * v;

        //terrain[ yi ] = contour * v;

        //terrain[ ri ] = contour * 0.3f;
        //terrain[ gi ] = contour * 0.3f;
        //terrain[ bi ] = contour * 0.3f;

        float o = 150.0f;
        float c = 75.0f;
        float w = 5000.0f;
        float h = 50.0f;

        float p = ( -1.0f / w ) * ( ( z - o ) * ( z - o ) );
        float k = powf( EULER, p ) * sin( 2.0f * x / c );

        terrain[ yi ] = k * h;

        terrain[ ri ] = k * 0.3f;
        terrain[ gi ] = k * 0.3f;
        terrain[ bi ] = k * 0.3f;
    }
}

static int init( struct app *app )
{
	( void )app;
	app_target_fps_set( app, 144 );
	app_target_tps_set( app, 30 );
	window_relative_mouse( true );
    terrain_init( 300 );
    terrain_rand();

    //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glEnable( GL_DEPTH_TEST );

	if ( shader_loadf( &shader, "res/shaders/2d.vert", "res/shaders/2d.frag" ) != 0 )
		exit( 1 );

	shader_bind( shader );

	vao = vao_create();
	vao_bind( vao );
	vbo = vbo_create( GL_ARRAY_BUFFER, false );
	vbo_bind( vbo );
	vbo_buff( vbo, ( void * ) terrain, list_size( terrain ) * sizeof( float ) );
	int position_idx = glGetAttribLocation( shader.handle, "position" );
	int color_idx    = glGetAttribLocation( shader.handle, "color" );
	vao_attr( vao, vbo, position_idx, 3, GL_FLOAT, sizeof( float ) * 6, 0 );
	vao_attr( vao, vbo, color_idx   , 3, GL_FLOAT, sizeof( float ) * 6, sizeof( float ) * 3 );

	camera_init( &camera, PERSPECTIVE );
    camera.fov   = PI / 4.0f;
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
        std::to_string( ( int ) ceilf( app->frame_avg ) ) + " | " +
        std::to_string( app->frame_delta ) + " | " +
        std::to_string( app->frame_target ) + " | " +
        std::to_string( app->frame_count );

	window_title_set( s.c_str() );

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

    if ( input_key_down( KB_T ) )
    {
        camera.type = camera.type == PERSPECTIVE ? ORTHOGRAPHIC : PERSPECTIVE;
        const char *type = camera.type == PERSPECTIVE ? "PERSPECTIVE" : "ORTHOGRAPHIC";
        log_debug( "Camera type: %s", type );
    }

    direction = vec3_normalize( direction );
    direction = vec3_scale( direction, 10.0f * app->frame_delta );
    camera.eye = vec3_add( camera.eye, direction );
    camera.aspect = window_aspect();
    camera.zoom += ( ( camera.zoom / 50.0f ) * input_mouse_scroll().y );

    if ( input_mouse_scroll().y != 0.0f )
    {
        log_debug( "Camera zoom: %f", camera.zoom );
    }

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

	glDrawArrays( GL_TRIANGLES, 0, point_count() );

    window_swap();

	return 0;
}
