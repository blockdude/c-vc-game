#ifndef SHADER_H
#define SHADER_H

#include <vcp/vcp.h>
#include <glad/gl.h>

struct VBO
{
    GLuint handle;
    GLint type;
    bool dyn;
};

struct VAO
{
    GLuint handle;
};

struct Shader
{
    GLuint handle;
    int status;
};

enum ShaderStatus
{
    SHADER_SUCCESS = 0,
    SHADER_VS_COMPILE_ERROR = 1,
    SHADER_FS_COMPILE_ERROR = 2,
    SHADER_PROGRAM_LINKING_ERROR = 3,
    SHADER_INVALID_FILE_PATH = 4,
};

struct VBO vbo_create(GLint type, bool dyn);
void vbo_free(struct VBO self);
void vbo_bind(struct VBO self);
void vbo_buff(struct VBO self, const void *data, size_t n);
//void vbo_sub_buff(void *data, size_t offset, size_t n);
struct VAO vao_create(void);
void vao_free(struct VAO self);
void vao_bind(struct VAO self);
void vao_attr(struct VAO self, struct VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);
struct Shader shader_loadf(const char *vspath, const char *fspath);
struct Shader shader_load(const char *vstext, const char *fstext);
void shader_free(struct Shader self);
void shader_bind(struct Shader self);
void shader_uniform_mat4(struct Shader self, const char *name, struct Mat4 m);
void shader_uniform_float(struct Shader self, const char *name, float f);
void shader_uniform_vec2(struct Shader self, const char *name, struct Vec2 v);
void shader_uniform_vec3(struct Shader self, const char *name, struct Vec3 v);
void shader_uniform_vec4(struct Shader self, const char *name, struct Vec4 v);
void shader_uniform_int(struct Shader self, const char *name, int v);
void shader_uniform_uint(struct Shader self, const char *name, unsigned int v);

#endif