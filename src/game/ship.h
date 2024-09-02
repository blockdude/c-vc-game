#ifndef SHIP_H
#define SHIP_H

#include <util/math.h>
#include <util/camera.h>
#include <graphics/gfx.h>
#include <system/window.h>

static float mesh[] = {
	 0.0f,  1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
	 0.0f,  0.0f, 1.0f,   1.0f, 1.0f, 1.0f,

	 0.0f,  1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
	 1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,

	 0.0f,  1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,

	 1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f
};

class Entity
{
public:
	float x;
	float y;

	vec2_t velocity;
	vec2_t direction;
	float rotation;
	struct vao vao;
	struct vbo vbo;
	struct shader shader;
	struct camera camera;

public:

	void Init( void )
	{
		this->velocity = { 0.0f, 0.0f };
		this->direction = { 0.0f, 0.0f };
		this->rotation = 0.0f;
		this->shader = shader_loadf( "res/shaders/2d.vert", "res/shaders/2d.frag" );
		this->vao = vao_create();
		this->vbo = vbo_create( GL_ARRAY_BUFFER, false );

		camera_init( &camera, ORTHOGRAPHIC );
		camera.eye.x = 0.0f;
		camera.eye.y = 0.0f;
		camera.eye.z = 0.0f;
		camera.pitch = DEGTORAD( 0 );
		camera.yaw = DEGTORAD( 0 );
		camera_update( &camera );

		vbo_buff( vbo, ( void * ) mesh, sizeof( mesh ) );

		int position_idx = glGetAttribLocation( shader.handle, "position" );
		int color_idx    = glGetAttribLocation( shader.handle, "color" );

		vao_attr( vao, vbo, position_idx, 3, GL_FLOAT, sizeof( float ) * 6, 0 );
		vao_attr( vao, vbo, color_idx   , 3, GL_FLOAT, sizeof( float ) * 6, sizeof( float ) * 3 );
	}

	void Tick( void )
	{
		direction = vec2_normalize( direction );
		velocity = vec2_add( velocity, vec2_scale( direction, 0.002f ) );
		velocity = vec2_sub( velocity, vec2_scale( velocity, 0.1f ) );
		x += velocity.x;
		y += velocity.y;

		camera.aspect = window_aspect();
		camera_update( &camera );
	}

	void Update( void )
	{
		this->direction = { 0.0f, 0.0f };
	}

	void Draw( void )
	{
		mat4_t model = mat4_scale( { 0.1f, 0.1f, 1.0f } );
		vec3_t pos   = { x, y, 0.0f };
		model = mat4_mul( model, mat4_translate( pos ) );

		shader_uniform_mat4( shader, "view_matrix", camera.view );
		shader_uniform_mat4( shader, "proj_matrix", camera.proj );
		shader_uniform_mat4( shader, "model_matrix", model );

		glDrawArrays( GL_LINES, 0, 8 );
	}
};

#endif
