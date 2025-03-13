#ifndef VCP_CAMERA_H
#define VCP_CAMERA_H

#include "types.h"

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

extern void camera_init(struct camera *camera, int type);
extern void camera_move(struct camera *camera, struct vec3 direction, float dist);
extern void camera_forward(struct camera *camera, float dist);
extern void camera_up(struct camera *camera, float dist);
extern void camera_right(struct camera *camera, float dist);
extern void camera_pitch(struct camera *camera, float angle);
extern void camera_yaw(struct camera *camera, float angle);
extern void camera_roll(struct camera *camera, float angle);
extern struct mat4 camera_proj(const struct camera *camera, float aspect, float near, float far);
extern struct mat4 camera_view(const struct camera *camera);

#endif
