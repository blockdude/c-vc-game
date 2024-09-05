#ifndef SHIP_H
#define SHIP_H

#include <math/math.h>
#include <math/vector.h>
#include <math/matrix.h>

#include <util/camera.h>
#include <util/log.h>

#include <graphics/gfx.h>

#include <system/window.h>

static float mesh[] = {
	 0.0f,  1.5f, 1.0f,   1.0f, 1.0f, 1.0f,
	 1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,

	 0.0f,  1.5f, 1.0f,   1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,

	 1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,


	 0.0f, -2.5f, 1.0f,   1.0f, 1.0f, 1.0f,
	-0.4f, -1.4f, 1.0f,   1.0f, 1.0f, 1.0f,

	-0.4f, -1.4f, 1.0f,   1.0f, 1.0f, 1.0f,
	 0.4f, -1.4f, 1.0f,   1.0f, 1.0f, 1.0f,

	 0.0f, -2.5f, 1.0f,   1.0f, 1.0f, 1.0f,
	 0.4f, -1.4f, 1.0f,   1.0f, 1.0f, 1.0f
};

class Entity
{
public:
	vec2_t move;
	float rotate;

	vec2_t position = { 0.0f };
	vec2_t velocity = { 0.0f };

	float angle = 0.0f;
	float angularVelocity = 0.0f;

	float acceleration = 0.001f;
	float angularAcceleration = 0.001f;

	float drag = 0.0000001f;
	float dampening = 0.0f;

private:
	struct vao vao;
	struct vbo vbo;
	struct shader shader;
	struct camera camera;

public:
	// units per second
	float Speed( void )
	{
		return 100.0f * vec2_len( velocity );
	}

	float AngularSpeed( void )
	{
		return 100.0f * angularVelocity;
	}

	// angle in radian
	float Angle( void )
	{
		return angle;
	}

	//hello
	void Init( void )
	{
		this->shader = shader_loadf( "res/shaders/2d.vert", "res/shaders/2d.frag" );
		this->vao = vao_create();
		this->vbo = vbo_create( GL_ARRAY_BUFFER, false );

		camera_init( &camera, ORTHOGRAPHIC );
		camera.zoom  = 0.025f;
		camera.eye.x = 0.0f;
		camera.eye.y = 0.0f;
		camera.eye.z = 0.0f;
		camera.pitch = DEGTORAD( 0 );
		camera.yaw   = DEGTORAD( 0 );
		camera_update( &camera );

		vbo_buff( vbo, ( void * ) mesh, sizeof( mesh ) );

		int position_idx = glGetAttribLocation( shader.handle, "position" );
		int color_idx    = glGetAttribLocation( shader.handle, "color" );

		vao_attr( vao, vbo, position_idx, 3, GL_FLOAT, sizeof( float ) * 6, 0 );
		vao_attr( vao, vbo, color_idx   , 3, GL_FLOAT, sizeof( float ) * 6, sizeof( float ) * 3 );
	}

	void Tick( void )
	{
		rotate = CLAMP( rotate, -1.0f, 1.0f );
		angularVelocity += rotate * angularAcceleration;
		angularVelocity -= angularVelocity * drag;

		angle = fmodf( angle + angularVelocity, PI * 2.0f );

		vec2_t direction = vec2_normalize( move );
		direction = vec2_rotate( direction, angle );
		direction = vec2_scale( direction, acceleration );

		velocity = vec2_add( velocity, direction );
		velocity = vec2_sub( velocity, vec2_scale( velocity, drag ) );
		position = vec2_add( position, velocity );

		camera.aspect = window_aspect();
		camera_update( &camera );
	}

	void Update( void )
	{
		this->move = { 0.0f, 0.0f };
		this->rotate = 0.0f;
	}

	void Draw( void )
	{
		mat4_t model = mat4_identity();
		model = mat4_mul( model, mat4_rotate_z( angle ) );
		model = mat4_mul( model, mat4_translate( { position.x, position.y, 0.0f } ) );

		shader_uniform_mat4( shader, "view_matrix", camera.view );
		shader_uniform_mat4( shader, "proj_matrix", camera.proj );
		shader_uniform_mat4( shader, "model_matrix", model );

		glDrawArrays( GL_LINES, 0, vec2_len( move ) > 0.0f ? 12 : 6 );
	}
};

#endif
