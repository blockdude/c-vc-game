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

	vec3 target = {
		cosf( self->pitch ) * sinf( self->yaw ),
		sinf( self->pitch ),
		cosf( self->pitch ) * cosf( self->yaw )
	};

	glm_vec3_copy( target, self->target );
	glm_vec3_normalize( self->target );

	glm_vec3_cross( ( vec3 ) { 0.0f, 1.0f, 0.0f }, self->target, self->right );
	glm_vec3_cross( self->target, self->right, self->up );

	vec3 center;
	glm_vec3_add( self->eye, self->target, center );
	glm_lookat( self->eye, center, self->up, self->view );
	glm_perspective( self->fov, self->aspect, self->znear, self->zfar, self->proj );
}
