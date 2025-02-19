#ifndef VCP_SHADER_H
#define VCP_SHADER_H

#include <glad/gl.h>
#include <util/types.h>

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
	int status;
};

#ifdef __cplusplus
extern "C" {
#endif

struct shader shader_loadf( const char *vspath, const char *fspath );
struct shader shader_load( const char *vstext, const char *fstext );
void shader_free( struct shader self );
void shader_bind( struct shader self );

void shader_uniform_mat4( struct shader self, const char *name, struct mat4 m );
void shader_uniform_float( struct shader self, const char *name, float f );
void shader_uniform_vec2( struct shader self, const char *name, struct vec2 v );
void shader_uniform_vec3( struct shader self, const char *name, struct vec3 v );
void shader_uniform_vec4( struct shader self, const char *name, struct vec4 v );
void shader_uniform_int( struct shader self, const char *name, int v );
void shader_uniform_uint( struct shader self, const char *name, unsigned int v );

#ifdef __cplusplus
}
#endif

#endif
