#ifndef VCP_VAO_H
#define VCP_VAO_H

#include "vbo.h"
#include <stddef.h>
#include <glad/gl.h>

struct vao
{
    GLuint handle;
};

extern struct vao vao_create(void);
extern void vao_free(struct vao self);
extern void vao_bind(struct vao self);
extern void vao_attr(struct vao self, struct vbo vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

#endif
