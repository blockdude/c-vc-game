#ifndef CAMERA_H
#define CAMERA_H

#include <util/types.h>

struct camera
{
	mat4_t view;
	mat4_t proj;

	vec3_t eye;		/* camera position */
	vec3_t target;	/* lookat position */
	vec3_t up;		/* camera tilt     */
	vec3_t right;

	float pitch;
	float yaw;
	float roll;
	float fov;
	float aspect;
	float znear;
	float zfar;
};

#ifdef __cplusplus
extern "C" {
#endif

void camera_init( struct camera *self, float fov );
void camera_update( struct camera *self );

#ifdef __cplusplus
}
#endif

#endif
