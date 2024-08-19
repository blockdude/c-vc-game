#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <cglm/struct.h>

enum shader_status
{
	SHADER_SUCCESS					= 0,
	SHADER_VS_COMPILE_ERROR			= 1,
	SHADER_FS_COMPILE_ERROR			= 2,
	SHADER_PROGRAM_LINKING_ERROR	= 3,
	SHADER_INVALID_FILE_PATH		= 4,
};

//struct VertexAttr
//{
//	GLuint index;
//	const GLchar *name;
//};

struct shader
{
	GLuint handle;
};

#ifdef __cplusplus
extern "C" {
#endif

int  shader_loadf( struct shader *self, const char *vspath, const char *fspath );
int  shader_load( struct shader *self, const char *vstext, size_t vslen, const char *fstext, size_t fslen );
void shader_free( struct shader self );
void shader_bind( struct shader self );

void shader_uniform_mat4( struct shader self, const char *name, mat4 m );
void shader_uniform_float( struct shader self, const char *name, float f );
void shader_uniform_vec2( struct shader self, const char *name, vec2 v );
void shader_uniform_vec3( struct shader self, const char *name, vec3 v );
void shader_uniform_vec4( struct shader self, const char *name, vec4 v );
void shader_uniform_int( struct shader self, const char *name, int v );
void shader_uniform_uint( struct shader self, const char *name, unsigned int v );

#ifdef __cplusplus
}
#endif

#endif
