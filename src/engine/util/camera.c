#include "camera.h"
#include <util/math.h>

void camera_init( struct camera *self, int type )
{
	*self = ( struct camera ) { 0 };

	self->type = type;

	self->fov = PI / 4.0f;
	self->aspect = 1.0f;
	self->near = 0.01f;
	self->far = 1000.0f;

	self->zoom = 1.0f;

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
	self->right  = vec3_cross( ( vec3_t ) { 0.0f, 1.0f, 0.0f }, direction );
	self->up     = vec3_cross( direction, self->right );
	self->view   = mat4_lookat( self->eye, self->target, self->up );

	if ( self->type == ORTHOGRAPHIC )
	{
		float top = self->fov / ( self->zoom * 2.0f );
		float right = top * self->aspect;
		self->proj = mat4_ortho( -right, right, -top, top, self->near, self->far );
	}
	else
	{
		self->proj = mat4_perspective( self->fov, self->aspect, self->near, self->far );
	}
}
