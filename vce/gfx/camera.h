#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>
#include <cglm/struct.h>

struct camera
{
	mat4s view;
	mat4s proj;

	vec3s eye;		/* camera position */
	vec3s target;	/* lookat position */
	vec3s up;		/* camera tilt     */
	vec3s right;

	float pitch;
	float yaw;
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
