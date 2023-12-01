#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

struct VertexAttr {
	GLuint index;
	const GLchar *name;
};

struct shader {
	GLuint handle;
	GLuint vs_handle;
	GLuint fs_handle;
};

int  shader_load( struct shader *shader, const char *vs, const char *fs );
void shader_free( struct shader self );
void shader_bind( struct shader self );

#endif
