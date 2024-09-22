#include <Renderer.h>

#include <graphics/vao.h>
#include <graphics/vbo.h>
#include <graphics/shader.h>
#include <util/camera.h>
#include <math/math.h>

#define BUFFERSIZE 2048

static struct vao vao;
static struct vbo vbo;
static struct shader shader;
static struct camera camera;
static color_t color;

void RendererInit( void )
{
	color = WHITE;
	shader = shader_loadf( "res/shaders/2d.vert", "res/shaders/2d.frag" );

	vao = vao_create();
	vbo = vbo_create( GL_ARRAY_BUFFER, true );
	vbo_buff( vbo, NULL, BUFFERSIZE );

	int position_idx = glGetAttribLocation( shader.handle, "position" );
	int color_idx    = glGetAttribLocation( shader.handle, "color" );

	vao_attr( vao, vbo, position_idx, 3, GL_FLOAT, sizeof( float ) * 6, 0 );
	vao_attr( vao, vbo, color_idx   , 3, GL_FLOAT, sizeof( float ) * 6, sizeof( float ) * 3 );

	camera_init( &camera, ORTHOGRAPHIC );
	camera.zoom = 0.02f;
	camera.eye.x = 0.0f;
	camera.eye.y = 0.0f;
	camera.eye.z = 0.0f;
	camera.pitch = DEGTORAD( 0 );
	camera.yaw   = DEGTORAD( 0 );
	camera_update( &camera );
}

void RendererColor( color_t c )
{
	color = c;
}

void RendererClear( void )
{
	glClearColor( color.r, color.g, color.b, color.a );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	// todo: clear vbo
}
