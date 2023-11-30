#include "camera.h"
#include "window.h"
#include <util/fmath.h>
#include <cglm/struct.h>

void camera_init( struct camera *self, float fov )
{
	*self = ( struct camera ){ 0 };

	self->fov = fov;
	self->aspect = window.aspect;
	self->znear = 0.01f;
	self->zfar = 1000.0f;

	camera_update( self );
}

void camera_update( struct camera *self )
{
	// bound pitch at +- pi/2 and yaw in [0, tau]
	self->pitch = clamp( self->pitch, -PI_2 + 0.000001f, PI_2 - 0.000001f );
	self->yaw = ( self->yaw < 0 ? TAU : 0.0f ) + fmodf( self->yaw, TAU );

	self->target = ( vec3s ) {{
		cosf( self->pitch ) * sinf( self->yaw ),
		sinf( self->pitch ),
		cosf( self->pitch ) * cosf( self->yaw )
	}};

	glms_vec3_normalize( self->target );

	self->right = glms_vec3_cross( ( vec3s ) {{ 0.0f, 1.0f, 0.0f }}, self->target );
	self->up = glms_vec3_cross( self->target, self->right );

	self->view = glms_lookat( self->eye, glms_vec3_add( self->eye, self->target ), self->up );
	self->proj = glms_perspective( self->fov, self->aspect, self->znear, self->zfar );
}
