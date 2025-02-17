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

	struct vec3 eye;	/* camera position */
	struct vec3 target;	/* lookat position */
	struct vec3 up;		/* camera tilt     */
	
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
void camera_move( struct camera *camera, struct vec3 direction, float dist );
void camera_forward( struct camera *camera, float dist );
void camera_up( struct camera *camera, float dist );
void camera_right( struct camera *camera, float dist );
void camera_pitch( struct camera *camera, float angle );
void camera_yaw( struct camera *camera, float angle );
void camera_roll( struct camera *camera, float angle );

// calculate matricies
struct mat4 camera_proj_custom( struct camera *camera, float aspect, float near, float far );
#define camera_proj( _cam, _aspect ) camera_proj_custom( _cam, _aspect, 0.01f, 1000.0f )
struct mat4 camera_view( struct camera *camera );

#ifdef __cplusplus
}
#endif

#endif
