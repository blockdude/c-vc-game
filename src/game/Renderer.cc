#include "Renderer.h"

#include <graphics/vao.h>
#include <graphics/vbo.h>
#include <graphics/shader.h>
#include <system/window.h>
#include <util/camera.h>
#include <util/log.h>
#include <math/math.h>
#include <math/matrix.h>
#include <math/vector.h>

#define BUFFERSIZE 4096

static int vertexCount;
static float vertexBuffer[ BUFFERSIZE ];

static struct vao vao;
static struct vbo vbo;
static struct shader shader;
static struct camera camera;
static color_t color;

void RendererInit( void )
{
	vertexCount = 0;
	shader = shader_loadf( "res/shaders/2d.vert", "res/shaders/2d.frag" );

	vao = vao_create();
	vbo = vbo_create( GL_ARRAY_BUFFER, true );
	vbo_buff( vbo, NULL, sizeof( vertexBuffer ) );

	int position_idx = glGetAttribLocation( shader.handle, "position" );
	int color_idx    = glGetAttribLocation( shader.handle, "color" );

	vao_attr( vao, vbo, position_idx, 3, GL_FLOAT, sizeof( float ) * 6, 0 );
	vao_attr( vao, vbo, color_idx   , 3, GL_FLOAT, sizeof( float ) * 6, sizeof( float ) * 3 );

	camera_init( &camera, ORTHOGRAPHIC );
	camera.zoom   = 0.05f;
	camera.eye    = { 0.0f, 0.0f,  1.0f };
	camera.target = { 0.0f, 0.0f, -1.0f };
	camera.up     = { 0.0f, 1.0f,  0.0f };
	camera_update( &camera );

	mat4_t model = mat4_identity();
	shader_uniform_mat4( shader, "view_matrix", camera_view( &camera ) );
	shader_uniform_mat4( shader, "proj_matrix", camera_proj( &camera, window_aspect() ) );
	shader_uniform_mat4( shader, "model_matrix", model );
}

void RendererColor( color_t c )
{
	color = c;
}

void RendererClear( void )
{
	glClearColor( color.r, color.g, color.b, color.a );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void RendererDraw( void )
{
	window_swap_buf();
}

void DrawTriangle( triangle_t tri, float rot )
{
	vertexBuffer[ vertexCount++ ] = tri.x0;
	vertexBuffer[ vertexCount++ ] = tri.y0;
	vertexBuffer[ vertexCount++ ] = 0.0f;

	vertexBuffer[ vertexCount++ ] = color.r;
	vertexBuffer[ vertexCount++ ] = color.g;
	vertexBuffer[ vertexCount++ ] = color.b;

	vertexBuffer[ vertexCount++ ] = tri.x1;
	vertexBuffer[ vertexCount++ ] = tri.y1;
	vertexBuffer[ vertexCount++ ] = 0.0f;

	vertexBuffer[ vertexCount++ ] = color.r;
	vertexBuffer[ vertexCount++ ] = color.g;
	vertexBuffer[ vertexCount++ ] = color.b;

	vertexBuffer[ vertexCount++ ] = tri.x2;
	vertexBuffer[ vertexCount++ ] = tri.y2;
	vertexBuffer[ vertexCount++ ] = 0.0f;

	vertexBuffer[ vertexCount++ ] = color.r;
	vertexBuffer[ vertexCount++ ] = color.g;
	vertexBuffer[ vertexCount++ ] = color.b;

	mat4_t model = mat4_rotate_z( rot );
	shader_uniform_mat4( shader, "model_matrix", model );

	glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( float ) * vertexCount, vertexBuffer );
	glDrawArrays( GL_TRIANGLES, 0, vertexCount );
	vertexCount = 0;
}

void DrawRectangle( rectangle_t rect, float rot )
{
	vertexBuffer[ vertexCount++ ] = -1.0f;
	vertexBuffer[ vertexCount++ ] = 1.0f;
	vertexBuffer[ vertexCount++ ] = 0.0f;

	vertexBuffer[ vertexCount++ ] = color.r;
	vertexBuffer[ vertexCount++ ] = color.g;
	vertexBuffer[ vertexCount++ ] = color.b;

	vertexBuffer[ vertexCount++ ] = 1.0f;
	vertexBuffer[ vertexCount++ ] = 1.0f;
	vertexBuffer[ vertexCount++ ] = 0.0f;

	vertexBuffer[ vertexCount++ ] = color.r;
	vertexBuffer[ vertexCount++ ] = color.g;
	vertexBuffer[ vertexCount++ ] = color.b;

	vertexBuffer[ vertexCount++ ] = -1.0f;
	vertexBuffer[ vertexCount++ ] = -1.0f;
	vertexBuffer[ vertexCount++ ] = 0.0f;

	vertexBuffer[ vertexCount++ ] = color.r;
	vertexBuffer[ vertexCount++ ] = color.g;
	vertexBuffer[ vertexCount++ ] = color.b;



	vertexBuffer[ vertexCount++ ] = 1.0f;
	vertexBuffer[ vertexCount++ ] = 1.0f;
	vertexBuffer[ vertexCount++ ] = 0.0f;

	vertexBuffer[ vertexCount++ ] = color.r;
	vertexBuffer[ vertexCount++ ] = color.g;
	vertexBuffer[ vertexCount++ ] = color.b;

	vertexBuffer[ vertexCount++ ] = 1.0f;
	vertexBuffer[ vertexCount++ ] = -1.0f;
	vertexBuffer[ vertexCount++ ] = 0.0f;

	vertexBuffer[ vertexCount++ ] = color.r;
	vertexBuffer[ vertexCount++ ] = color.g;
	vertexBuffer[ vertexCount++ ] = color.b;

	vertexBuffer[ vertexCount++ ] = -1.0f;
	vertexBuffer[ vertexCount++ ] = -1.0f;
	vertexBuffer[ vertexCount++ ] = 0.0f;

	vertexBuffer[ vertexCount++ ] = color.r;
	vertexBuffer[ vertexCount++ ] = color.g;
	vertexBuffer[ vertexCount++ ] = color.b;

	mat4_t t = mat4_translate( { rect.x, rect.y, 0.0f } );
	mat4_t r = mat4_rotate_z( rot );
	mat4_t s = mat4_scale( { rect.w, rect.h, 0.0f } );

	// S * R * T
	mat4_t model = mat4_identity();
	model = mat4_mul( t, model );
	model = mat4_mul( r, model );
	model = mat4_mul( s, model );

	shader_uniform_mat4( shader, "model_matrix", model );

	glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( float ) * vertexCount, vertexBuffer );
	glDrawArrays( GL_TRIANGLES, 0, vertexCount );
	vertexCount = 0;
}
