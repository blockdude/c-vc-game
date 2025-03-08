#include "camera.h"
#include "../math/math.h"
#include "../math/vec3.h"
#include "../math/mat4.h"

void camera_init( struct camera *const self, const int type )
{
	*self = ( struct camera ) { 0 };

	self->type   = type;
	self->eye    = ( struct vec3 ) { 0.0f, 0.0f, 0.0f };
	self->target = ( struct vec3 ) { 0.0f, 0.0f, 1.0f };
	self->up     = ( struct vec3 ) { 0.0f, 1.0f, 0.0f };
	self->fov    = ( float ) PI / 4.0f;
	self->zoom   = 1.0f;
}

void camera_move( struct camera *const self, const struct vec3 direction, const float dist )
{
	const struct vec3 move = vec3_scale( vec3_normalize( direction ), dist );
	self->eye = vec3_add( self->eye, move );
	self->target = vec3_add( self->target, move );
}

void camera_forward( struct camera *const self, const float dist )
{
	struct vec3 direction = vec3_sub( self->target, self->eye );
	direction = vec3_normalize( direction );

	const struct vec3 move = vec3_scale( direction, dist );
	self->eye = vec3_add( self->eye, move );
	self->target = vec3_add( self->target, move );
}

void camera_up( struct camera *const self, const float dist )
{
	struct vec3 direction = self->up;
	direction = vec3_normalize( direction );

	const struct vec3 move = vec3_scale( direction, dist );
	self->eye = vec3_add( self->eye, move );
	self->target = vec3_add( self->target, move );
}

void camera_right( struct camera *const self, const float dist )
{
	struct vec3 forward = vec3_sub( self->target, self->eye );
	forward = vec3_normalize( forward );

	const struct vec3 up = vec3_normalize( self->up );

	struct vec3 direction = vec3_cross( forward, up );
	direction = vec3_normalize( direction );

	const struct vec3 move = vec3_scale( direction, dist );

	self->eye = vec3_add( self->eye, move );
	self->target = vec3_add( self->target, move );
}

void camera_pitch( struct camera *const self, const float angle )
{
	struct vec3 forward = vec3_sub( self->target, self->eye );
	forward = vec3_normalize( forward );

	const struct vec3 up = vec3_normalize( self->up );

	// right axis
	struct vec3 axis = vec3_cross( forward, up );
	axis = vec3_normalize( axis );

	struct vec3 direction = vec3_sub( self->target, self->eye );
	direction = vec3_rotate_around_axis( direction, axis, angle );

	self->up = vec3_rotate_around_axis( self->up, axis, angle );
	self->target = vec3_add( self->eye, direction );
}

void camera_yaw( struct camera *const self, const float angle )
{
	// up axis
	const struct vec3 axis = vec3_normalize( self->up );

	struct vec3 direction = vec3_sub( self->target, self->eye );
	direction = vec3_rotate_around_axis( direction, axis, angle );
	
	self->target = vec3_add( self->eye, direction );
}

void camera_roll( struct camera *const self, float angle )
{
	// forward axis
	struct vec3 axis = vec3_sub( self->target, self->eye );
	axis = vec3_normalize( axis );

	struct vec3 direction = vec3_sub( self->target, self->eye );
	direction = vec3_rotate_around_axis( direction, axis, angle );
	
	self->up = vec3_rotate_around_axis( self->up, axis, angle );
	self->target = vec3_add( self->eye, direction );
}

struct mat4 camera_proj( const struct camera *const self, const float aspect, const float near, const float far )
{
	if ( self->type == ORTHOGRAPHIC )
	{
		const float top = 1.0f / self->zoom;
		const float right = top * aspect;
		return mat4_ortho( -right, right, -top, top, near, far );
	}

	else if ( self->type == PERSPECTIVE )
	{
		return mat4_perspective( self->fov, aspect, near, far );
	}

	return mat4_identity();
}

struct mat4 camera_view( const struct camera *const self )
{
	return mat4_lookat( self->eye, self->target, self->up );
}
