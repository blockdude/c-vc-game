#ifndef CAMERA_H
#define CAMERA_H

#include <util/types.h>

enum camera_type
{
	PERSPECTIVE,
	ORTHOGRAPHIC,
};

struct camera
{
	// projection type
	int type;

	mat4_t view;

	/*
	 * The projection matrix should be obtained by an external
	 * function because it never changes unless the aspect ratio
	 * changes or the fov changes so it is not great to have it
	 * updated every frame. I will keep it till I figure out what
	 * to do.
	 */
	mat4_t proj;

	vec3_t eye;		/* camera position */
	vec3_t target;	/* lookat position */
	vec3_t up;		/* camera tilt     */

	float pitch;
	float yaw;
	float roll;

	float aspect;

	/*
	 * FYI: the z in znear and zfar mean the z axis which is the
	 * depth axis. This should have been obvious but im stupid.
	 */
	float near;
	float far;
	
	// perspective
	float fov;

	// orthographic - controls the size of the near and far clipping planes
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
