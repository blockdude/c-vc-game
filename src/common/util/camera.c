#include "camera.h"
#include <math/math.h>
#include <math/vector.h>
#include <math/matrix.h>

void camera_init( struct camera *self, int type )
{
	*self = ( struct camera ) { 0 };

	self->type   = type;
	self->eye    = ( vec3_t ) { 0.0f, 0.0f, 0.0f };
	self->target = ( vec3_t ) { 0.0f, 0.0f, 1.0f };
	self->up     = ( vec3_t ) { 0.0f, 1.0f, 0.0f };
	self->fov    = PI / 4.0f;
	self->zoom   = 1.0f;

	camera_update( self );
}

void camera_update( struct camera *self )
{
	( void ) self;
}

void camera_move( struct camera *self, vec3_t direction, float dist )
{
	direction = vec3_normalize( direction );
	vec3_t move = vec3_scale( direction, dist );

	self->eye = vec3_add( self->eye, move );
	self->target = vec3_add( self->target, move );
}

void camera_forward( struct camera *self, float dist )
{
	vec3_t direction;
	direction = vec3_sub( self->target, self->eye );
	direction = vec3_normalize( direction );

	vec3_t move = vec3_scale( direction, dist );

	self->eye = vec3_add( self->eye, move );
	self->target = vec3_add( self->target, move );
}

void camera_up( struct camera *self, float dist )
{
	vec3_t direction = self->up;
	direction = vec3_normalize( direction );

	vec3_t move = vec3_scale( direction, dist );

	self->eye = vec3_add( self->eye, move );
	self->target = vec3_add( self->target, move );
}

void camera_right( struct camera *self, float dist )
{
	vec3_t forward;
	forward = vec3_sub( self->target, self->eye );
	forward = vec3_normalize( forward );

	vec3_t up;
	up = vec3_normalize( self->up );

	vec3_t direction;
	direction = vec3_cross( forward, up );
	direction = vec3_normalize( direction );

	vec3_t move = vec3_scale( direction, dist );

	self->eye = vec3_add( self->eye, move );
	self->target = vec3_add( self->target, move );
}

void camera_pitch( struct camera *self, float angle )
{
	vec3_t forward;
	forward = vec3_sub( self->target, self->eye );
	forward = vec3_normalize( forward );

	vec3_t up;
	up = vec3_normalize( self->up );

	// right axis
	vec3_t axis;
	axis = vec3_cross( forward, up );
	axis = vec3_normalize( axis );

	vec3_t direction = vec3_sub( self->target, self->eye );
	direction = vec3_rotate_around_axis( direction, axis, angle );

	self->up = vec3_rotate_around_axis( self->up, axis, angle );
	self->target = vec3_add( self->eye, direction );
}

void camera_yaw( struct camera *self, float angle )
{
	// up axis
	vec3_t axis;
	axis = vec3_normalize( self->up );

	vec3_t direction;
	direction = vec3_sub( self->target, self->eye );
	direction = vec3_rotate_around_axis( direction, axis, angle );
	
	self->target = vec3_add( self->eye, direction );
}

void camera_roll( struct camera *self, float angle )
{
	// forward axis
	vec3_t axis;
	axis = vec3_sub( self->target, self->eye );
	axis = vec3_normalize( axis );

	vec3_t direction;
	direction = vec3_sub( self->target, self->eye );
	direction = vec3_rotate_around_axis( direction, axis, angle );
	
	self->up = vec3_rotate_around_axis( self->up, axis, angle );
	self->target = vec3_add( self->eye, direction );
}

mat4_t camera_view( struct camera *self )
{
	return mat4_lookat( self->eye, self->target, self->up );
}

mat4_t camera_proj_custom( struct camera *self, float aspect, float near, float far )
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
