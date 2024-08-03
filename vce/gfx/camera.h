#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>
#include <cglm/struct.h>

struct camera
{
	mat4 view;
	mat4 proj;

	vec3 eye;		/* camera position */
	vec3 target;	/* lookat position */
	vec3 up;		/* camera tilt     */
	vec3 right;

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
