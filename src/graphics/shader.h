#ifndef VCP_SHADER_H
#define VCP_SHADER_H

#include "../util/types.h"
#include <glad/gl.h>

enum shader_status
{
    SHADER_SUCCESS = 0,
    SHADER_VS_COMPILE_ERROR = 1,
    SHADER_FS_COMPILE_ERROR = 2,
    SHADER_PROGRAM_LINKING_ERROR = 3,
    SHADER_INVALID_FILE_PATH = 4,
};

struct shader
{
    GLuint handle;
    int status;
};

extern struct shader shader_loadf(const char *vspath, const char *fspath);
extern struct shader shader_load(const char *vstext, const char *fstext);
extern void shader_free(struct shader self);
extern void shader_bind(struct shader self);
extern void shader_uniform_mat4(struct shader self, const char *name, struct mat4 m);
extern void shader_uniform_float(struct shader self, const char *name, float f);
extern void shader_uniform_vec2(struct shader self, const char *name, struct vec2 v);
extern void shader_uniform_vec3(struct shader self, const char *name, struct vec3 v);
extern void shader_uniform_vec4(struct shader self, const char *name, struct vec4 v);
extern void shader_uniform_int(struct shader self, const char *name, int v);
extern void shader_uniform_uint(struct shader self, const char *name, unsigned int v);

#endif
