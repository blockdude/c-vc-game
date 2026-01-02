#include <vcp/vcp.h>

void camera_init(struct Camera *self, int type)
{
    *self = (struct Camera){ 0 };

    self->type   = type;
    self->eye    = (struct Vec3){ 0.0f, 0.0f, 0.0f };
    self->target = (struct Vec3){ 0.0f, 0.0f, 1.0f };
    self->up     = (struct Vec3){ 0.0f, 1.0f, 0.0f };
    self->fov    = (float)PI / 4.0f;
    self->zoom   = 1.0f;
}

void camera_move(struct Camera *self, struct Vec3 direction, float dist)
{
    struct Vec3 move = vec3_scale(vec3_normalize(direction), dist);
    self->eye = vec3_add(self->eye, move);
    self->target = vec3_add(self->target, move);
}

void camera_forward(struct Camera *self, float dist)
{
    struct Vec3 direction = vec3_sub(self->target, self->eye);
    direction = vec3_normalize(direction);

    struct Vec3 move = vec3_scale(direction, dist);
    self->eye = vec3_add(self->eye, move);
    self->target = vec3_add(self->target, move);
}

void camera_up(struct Camera *self, float dist)
{
    struct Vec3 direction = self->up;
    direction = vec3_normalize(direction);

    struct Vec3 move = vec3_scale(direction, dist);
    self->eye = vec3_add(self->eye, move);
    self->target = vec3_add(self->target, move);
}

void camera_right(struct Camera *self, float dist)
{
    struct Vec3 forward = vec3_sub(self->target, self->eye);
    forward = vec3_normalize(forward);

    struct Vec3 up = vec3_normalize(self->up);

    struct Vec3 direction = vec3_cross(forward, up);
    direction = vec3_normalize(direction);

    struct Vec3 move = vec3_scale(direction, dist);

    self->eye = vec3_add(self->eye, move);
    self->target = vec3_add(self->target, move);
}

void camera_pitch(struct Camera *self, float angle)
{
    struct Vec3 forward = vec3_sub(self->target, self->eye);
    forward = vec3_normalize(forward);

    struct Vec3 up = vec3_normalize(self->up);

    // right axis
    struct Vec3 axis = vec3_cross(forward, up);
    axis = vec3_normalize(axis);

    struct Vec3 direction = vec3_sub(self->target, self->eye);
    direction = vec3_rotate_around_axis(direction, axis, angle);

    self->up = vec3_rotate_around_axis(self->up, axis, angle);
    self->target = vec3_add(self->eye, direction);
}

void camera_yaw(struct Camera *self, float angle)
{
    // up axis
    struct Vec3 axis = vec3_normalize(self->up);

    struct Vec3 direction = vec3_sub(self->target, self->eye);
    direction = vec3_rotate_around_axis(direction, axis, angle);

    self->target = vec3_add(self->eye, direction);
}

void camera_roll(struct Camera *self, float angle)
{
    // forward axis
    struct Vec3 axis = vec3_sub(self->target, self->eye);
    axis = vec3_normalize(axis);

    struct Vec3 direction = vec3_sub(self->target, self->eye);
    direction = vec3_rotate_around_axis(direction, axis, angle);

    self->up = vec3_rotate_around_axis(self->up, axis, angle);
    self->target = vec3_add(self->eye, direction);
}

struct Mat4 camera_proj(const struct Camera *self, float aspect, float near, float far)
{
    if (self->type == ORTHOGRAPHIC)
    {
        const float top = 1.0f / self->zoom;
        const float right = top * aspect;
        return mat4_ortho(-right, right, -top, top, near, far);
    }

    else if (self->type == PERSPECTIVE)
    {
        return mat4_perspective(self->fov, aspect, near, far);
    }

    return mat4_identity();
}

struct Mat4 camera_view(const struct Camera *self)
{
    return mat4_lookat(self->eye, self->target, self->up);
}
