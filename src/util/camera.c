#include "camera.h"
#include "../math/math.h"
#include "../math/vec3.h"
#include "../math/mat4.h"

void camera_init( struct camera *self, int type )
{
	*self = ( struct camera ) { 0 };

	self->type   = type;
	self->eye    = ( struct vec3 ) { 0.0f, 0.0f, 0.0f };
	self->target = ( struct vec3 ) { 0.0f, 0.0f, 1.0f };
	self->up     = ( struct vec3 ) { 0.0f, 1.0f, 0.0f };
	self->fov    = ( float ) PI / 4.0f;
	self->zoom   = 1.0f;

	camera_update( self );
}

void camera_update( struct camera *self )
{
	( void ) self;
}

void camera_move( struct camera *self, struct vec3 direction, float dist )
{
	direction = vec3_normalize( direction );
	struct vec3 move = vec3_scale( direction, dist );

	self->eye = vec3_add( self->eye, move );
	self->target = vec3_add( self->target, move );
}

void camera_forward( struct camera *self, float dist )
{
	struct vec3 direction;
	direction = vec3_sub( self->target, self->eye );
	direction = vec3_normalize( direction );

	struct vec3 move = vec3_scale( direction, dist );

	self->eye = vec3_add( self->eye, move );
	self->target = vec3_add( self->target, move );
}

void camera_up( struct camera *self, float dist )
{
	struct vec3 direction = self->up;
	direction = vec3_normalize( direction );

	struct vec3 move = vec3_scale( direction, dist );

	self->eye = vec3_add( self->eye, move );
	self->target = vec3_add( self->target, move );
}

void camera_right( struct camera *self, float dist )
{
	struct vec3 forward;
	forward = vec3_sub( self->target, self->eye );
	forward = vec3_normalize( forward );

	struct vec3 up;
	up = vec3_normalize( self->up );

	struct vec3 direction;
	direction = vec3_cross( forward, up );
	direction = vec3_normalize( direction );

	struct vec3 move = vec3_scale( direction, dist );

	self->eye = vec3_add( self->eye, move );
	self->target = vec3_add( self->target, move );
}

void camera_pitch( struct camera *self, float angle )
{
	struct vec3 forward;
	forward = vec3_sub( self->target, self->eye );
	forward = vec3_normalize( forward );

	struct vec3 up;
	up = vec3_normalize( self->up );

	// right axis
	struct vec3 axis;
	axis = vec3_cross( forward, up );
	axis = vec3_normalize( axis );

	struct vec3 direction = vec3_sub( self->target, self->eye );
	direction = vec3_rotate_around_axis( direction, axis, angle );

	self->up = vec3_rotate_around_axis( self->up, axis, angle );
	self->target = vec3_add( self->eye, direction );
}

void camera_yaw( struct camera *self, float angle )
{
	// up axis
	struct vec3 axis;
	axis = vec3_normalize( self->up );

	struct vec3 direction;
	direction = vec3_sub( self->target, self->eye );
	direction = vec3_rotate_around_axis( direction, axis, angle );
	
	self->target = vec3_add( self->eye, direction );
}

void camera_roll( struct camera *self, float angle )
{
	// forward axis
	struct vec3 axis;
	axis = vec3_sub( self->target, self->eye );
	axis = vec3_normalize( axis );

	struct vec3 direction;
	direction = vec3_sub( self->target, self->eye );
	direction = vec3_rotate_around_axis( direction, axis, angle );
	
	self->up = vec3_rotate_around_axis( self->up, axis, angle );
	self->target = vec3_add( self->eye, direction );
}

struct mat4 camera_view( struct camera *self )
{
	return mat4_lookat( self->eye, self->target, self->up );
}

struct mat4 camera_proj( struct camera *self, float aspect, float near, float far )
{
	if ( self->type == ORTHOGRAPHIC )
	{
		float top = 1.0f / self->zoom;
		float right = top * aspect;
		return mat4_ortho( -right, right, -top, top, near, far );
	}

	else if ( self->type == PERSPECTIVE )
	{
		return mat4_perspective( self->fov, aspect, near, far );
	}

	return mat4_identity();
}
