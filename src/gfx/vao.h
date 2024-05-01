#ifndef VAO_H
#define VAO_H

#include "vbo.h"
#include <stddef.h>
#include <glad/glad.h>

struct vao
{
	GLuint handle;
};

struct vao vao_create( void );
void vao_free( struct vao self );
void vao_bind( struct vao self );
void vao_attr( struct vao self, struct vbo vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

#endif
