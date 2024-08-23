#include "camera.h"
#include "window.h"
#include "util/math.h"
#include "util/log.h"
#include <cglm/cglm.h>

void camera_init( struct camera *self, float fov )
{
	*self = ( struct camera ) { 0 };

	self->fov = fov;
	self->aspect = window.aspect;
	self->znear = 0.01f;
	self->zfar = 1000.0f;

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

	vec3 geye = { self->eye.x, self->eye.y, self->eye.z };
	vec3 gcen = { center.x, center.y, center.z };
	vec3 gup  = { self->up.x, self->up.y, self->up.z };

	mat4 view;
	mat4 proj;

	glm_lookat( geye, gcen, gup, view );
	glm_perspective( self->fov, self->aspect, self->znear, self->zfar, proj );

	self->view = ( mat4_t ) {
		view[ 0 ][ 0 ], view[ 0 ][ 1 ], view[ 0 ][ 2 ], view[ 0 ][ 3 ],
		view[ 1 ][ 0 ], view[ 1 ][ 1 ], view[ 1 ][ 2 ], view[ 1 ][ 3 ],
		view[ 2 ][ 0 ], view[ 2 ][ 1 ], view[ 2 ][ 2 ], view[ 2 ][ 3 ],
		view[ 3 ][ 0 ], view[ 3 ][ 1 ], view[ 3 ][ 2 ], view[ 3 ][ 3 ]
	};

	self->proj = ( mat4_t ) {
		proj[ 0 ][ 0 ], proj[ 0 ][ 1 ], proj[ 0 ][ 2 ], proj[ 0 ][ 3 ],
		proj[ 1 ][ 0 ], proj[ 1 ][ 1 ], proj[ 1 ][ 2 ], proj[ 1 ][ 3 ],
		proj[ 2 ][ 0 ], proj[ 2 ][ 1 ], proj[ 2 ][ 2 ], proj[ 2 ][ 3 ],
		proj[ 3 ][ 0 ], proj[ 3 ][ 1 ], proj[ 3 ][ 2 ], proj[ 3 ][ 3 ]
	};

	log_debug(
		"\n ===VIEW MATRIX - GLMLIB=== \n"
		"%6.2f %6.2f %6.2f %6.2f\n"
		"%6.2f %6.2f %6.2f %6.2f\n"
		"%6.2f %6.2f %6.2f %6.2f\n"
		"%6.2f %6.2f %6.2f %6.2f",
        self->view.m00, self->view.m01, self->view.m02, self->view.m03,
        self->view.m10, self->view.m11, self->view.m12, self->view.m13,
        self->view.m20, self->view.m21, self->view.m22, self->view.m23,
        self->view.m30, self->view.m31, self->view.m32, self->view.m33
	);

	self->view = mat4_lookat( self->eye, center, self->up );
	//self->view = mat6_transpose( self->view );
	self->proj = mat4_perspective( self->fov, self->aspect, self->znear, self->zfar );

	log_debug(
		"\n ===VIEW MATRIX - RAYLIB=== \n"
		"%6.2f %6.2f %6.2f %6.2f\n"
		"%6.2f %6.2f %6.2f %6.2f\n"
		"%6.2f %6.2f %6.2f %6.2f\n"
		"%6.2f %6.2f %6.2f %6.2f",
        self->view.m00, self->view.m01, self->view.m02, self->view.m03,
        self->view.m10, self->view.m11, self->view.m12, self->view.m13,
        self->view.m20, self->view.m21, self->view.m22, self->view.m23,
        self->view.m30, self->view.m31, self->view.m32, self->view.m33
	);
}
