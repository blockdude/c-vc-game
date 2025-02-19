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

struct vbo vbo_create( GLint type, bool dyn );
void vbo_free( struct vbo self );
void vbo_bind( struct vbo self );
void vbo_buff( struct vbo self, void *data, size_t n );
//void vbo_sub_buff( void *data, size_t offset, size_t n );

#ifdef __cplusplus
}
#endif

#endif
