#ifndef VCP_VBO_H
#define VCP_VBO_H

#include <glad/gl.h>
#include <stdbool.h>
#include <stddef.h>

struct vbo
{
    GLuint handle;
    GLint type;
    bool dyn;
};

#ifdef __cplusplus
extern "C" {
#endif

extern struct vbo vbo_create(GLint type, bool dyn);
extern void vbo_free(struct vbo self);
extern void vbo_bind(struct vbo self);
extern void vbo_buff(struct vbo self, const void *data, size_t n);
//void vbo_sub_buff( void *data, size_t offset, size_t n );

#ifdef __cplusplus
}
#endif

#endif
