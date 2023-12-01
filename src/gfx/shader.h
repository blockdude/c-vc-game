#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <cglm/struct.h>

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

void shader_uniform_mat4( struct shader self, char *name, mat4s m );
void shader_uniform_float( struct shader self, char *name, float f );
void shader_uniform_vec2( struct shader self, char *name, vec2s v );
void shader_uniform_vec3( struct shader self, char *name, vec3s v );
void shader_uniform_vec4( struct shader self, char *name, vec4s v );
void shader_uniform_int( struct shader self, char *name, int v );
void shader_uniform_uint( struct shader self, char *name, unsigned int v );

#endif
