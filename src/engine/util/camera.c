#include "camera.h"
#include <system/core-internal.h>
#include <util/math.h>

void camera_init( struct camera *self, int type )
{
	*self = ( struct camera ) { 0 };

	self->type = type;

	self->fov = PI / 4.0f;
	self->aspect = 1.0f;
	self->znear = 0.01f;
	self->zfar = 1000.0f;

	self->zoom = 1.0f;

	camera_update( self );
}

void camera_update( struct camera *self )
{
	// bound pitch at +- pi/2 and yaw in [0, tau]
	self->pitch = CLAMP( self->pitch, -PI_2 + EPSILON, PI_2 - EPSILON );
	self->yaw = ( self->yaw < 0 ? TAU : 0.0f ) + fmodf( self->yaw, TAU );

	vec3_t target = {
		cosf( self->pitch ) * sinf( self->yaw ),
		sinf( self->pitch ),
		cosf( self->pitch ) * cosf( self->yaw )
	};

	self->target = vec3_normalize( target );
	self->right  = vec3_cross( ( vec3_t ) { 0.0f, 1.0f, 0.0f }, self->target );
	self->up     = vec3_cross( self->target, self->right );

	vec3_t center = vec3_add( self->eye, self->target );

	self->view = mat4_lookat( self->eye, center, self->up );

	if ( self->type == ORTHOGRAPHIC )
	{
		self->proj = mat4_ortho( -1.0f * self->zoom, 1.0f * self->zoom, -1.0f * self->zoom, 1.0f * self->zoom, 0.0f, 100.0f );
	}
	else
	{
		self->proj = mat4_perspective( self->fov, self->aspect, self->znear, self->zfar );
	}
}
