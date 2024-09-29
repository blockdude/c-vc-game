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
	// projection type
	int type;

	vec3_t eye;		/* camera position */
	vec3_t target;	/* lookat position */
	vec3_t up;		/* camera tilt     */

	// I want to get rid of these in favor of functions
	float pitch;
	float yaw;
	float roll;
	
	// perspective - controls the Y field of view
	float fov;

	// orthographic - controls the size of the near and far clipping planes
	float zoom;
};

#ifdef __cplusplus
extern "C" {
#endif

void camera_init( struct camera *camera, int type );
void camera_update( struct camera *camera );

void camera_forward( struct camera *camera, float dist );
void camera_up( struct camera *camera, float dist );
void camera_right( struct camera *camera, float dist );

void camera_pitch( struct camera *camera, float angle );
void camera_yaw( struct camera *camera, float angle );
void camera_roll( struct camera *camera, float angle );

/*
 * Calculate the proction matrix of the camera
 */
mat4_t camera_proj_custom( struct camera *camera, float aspect, float near, float far );
#define camera_proj( _cam, _aspect ) camera_proj_custom( _cam, _aspect, 0.01f, 1000.0f )

/*
 * Calculate the view matrix of the camera
 */
mat4_t camera_view( struct camera *camera );

#ifdef __cplusplus
}
#endif

#endif
