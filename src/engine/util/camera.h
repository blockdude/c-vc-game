#ifndef CAMERA_H
#define CAMERA_H

#include <util/types.h>

enum camera_type
{
	PERSPECTIVE,
	ORTHOGRAPHIC
};

struct camera
{
	int type;

	mat4_t view;
	mat4_t proj;

	vec3_t eye;		/* camera position */
	vec3_t target;	/* lookat position */
	vec3_t up;		/* camera tilt     */
	vec3_t right;   /* idk             */

	float pitch;
	float yaw;
	float roll;
	float aspect;

	float fov;
	
	/*
	 * FYI: the z in znear and zfar mean the z axis
	 */

	float near;
	float far;

	float zoom;
};

#ifdef __cplusplus
extern "C" {
#endif

void camera_init( struct camera *self, int type );
void camera_update( struct camera *self );

#ifdef __cplusplus
}
#endif

#endif
