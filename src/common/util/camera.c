#include "camera.h"
#include <math/math.h>
#include <math/vector.h>
#include <math/matrix.h>

void camera_init( struct camera *self, int type )
{
	*self = ( struct camera ) { 0 };

	self->type   = type;
	self->eye    = ( vec3_t ) { 0 };
	self->target = ( vec3_t ) { 0.0f, 0.0f, 1.0f };
	self->up     = ( vec3_t ) { 0.0f, 1.0f, 0.0f };
	self->fov    = PI / 4.0f;
	self->zoom   = 1.0f;

	camera_update( self );
}

void camera_update( struct camera *self )
{
	// bound pitch at +- pi/2 and yaw in [0, tau]
	self->pitch = CLAMP( self->pitch, -PI_2 + EPSILON, PI_2 - EPSILON );
	self->yaw = ( self->yaw < 0 ? TAU : 0.0f ) + fmodf( self->yaw, TAU );

	vec3_t direction = {
		cosf( self->pitch ) * sinf( self->yaw ),
		sinf( self->pitch ),
		cosf( self->pitch ) * cosf( self->yaw )
	};

	direction    = vec3_normalize( direction );
	self->target = vec3_add( self->eye, direction );
	self->up     = ( vec3_t ) { 0.0f, 1.0f, 0.0f };
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
