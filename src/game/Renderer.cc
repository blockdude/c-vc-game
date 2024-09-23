#include <Renderer.h>

#include <graphics/vao.h>
#include <graphics/vbo.h>
#include <graphics/shader.h>
#include <system/window.h>
#include <util/camera.h>
#include <math/math.h>
#include <math/matrix.h>
#include <math/vector.h>

#define BUFFERSIZE 2048

static int vertexCount;
static struct vao vao;
static struct vbo vbo;
static struct shader shader;
static struct camera camera;
static color_t color;

void RendererInit( void )
{
	vertexCount = 0;
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

void RendererDraw( void )
{
	//mat4_t model = mat4_identity();
	//model = mat4_mul( model, mat4_rotate_z( angle ) );
	//model = mat4_mul( model, mat4_translate( { position.x, position.y, 0.0f } ) );

	//shader_uniform_mat4( shader, "view_matrix", camera.view );
	//shader_uniform_mat4( shader, "proj_matrix", camera.proj );
	//shader_uniform_mat4( shader, "model_matrix", model );

	//glDrawArrays( GL_LINES, 0, vec2_len( move ) > 0.0f ? 12 : 6 );
	window_swap();
}
