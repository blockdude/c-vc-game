#ifndef SHIP_H
#define SHIP_H

#include <util/math.h>
#include <util/camera.h>
#include <graphics/gfx.h>

static float mesh[] = {
	-1.0f, -1.0f, 1.0f,   0.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, 1.0f,   0.0f, 0.0f, 0.0f,
	 1.0f,  1.0f, 1.0f,   0.0f, 0.0f, 0.0f,

	 1.0f,  1.0f, 1.0f,   0.0f, 0.0f, 0.0f,
	-1.0f,  1.0f, 1.0f,   0.0f, 0.0f, 0.0f,
	-1.0f, -1.0f, 1.0f,   0.0f, 0.0f, 0.0f
};

class Entity
{
public:
	mat4_t transform;
	vec3_t velocity;
	float rotation;
	struct vao vao;
	struct vbo vbo;
	struct shader shader;
	struct camera camera;

public:

	void Init( void )
	{
		this->transform = mat4_scale( { 0.1f, 0.1f, 1.0f } );
		this->velocity = { 0.0f, 0.0f, 0.0f };
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
		transform = mat4_mul( mat4_translate( velocity ), transform );
		camera_update( &camera );
	}

	void Update( void )
	{
		this->velocity = { 0.0f, 0.0f, 0.0f };
	}

	void Draw( void )
	{
		shader_uniform_mat4( shader, "view_matrix", camera.view );
		shader_uniform_mat4( shader, "proj_matrix", camera.proj );
		shader_uniform_mat4( shader, "model_matrix", transform );

		glDrawArrays( GL_TRIANGLES, 0, 6 );
	}
};

#endif
