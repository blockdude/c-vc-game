#include <vcp/vcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static inline char *shader_get_log(
    const GLint handle,
    void (*getlog)(GLuint, GLsizei, GLsizei *, GLchar *),
    void (*getiv)(GLuint, GLenum, GLint *))
{
    GLint loglen = 0;
    getiv(handle, GL_INFO_LOG_LENGTH, &loglen);

    if (loglen <= 1)
        return NULL;

    char *logtext = malloc(loglen * sizeof(*logtext));
    getlog(handle, loglen, NULL, logtext);

    return logtext;
}

static char *shader_load_text(const char *path, size_t *out_len)
{
    FILE *f = NULL;
    char *text = NULL;
    size_t len = 0;

    f = fopen(path, "rb");
    if (f == NULL)
    {
        log_warn("Could not open shader file: %s", path);
        return NULL;
    }

    // put shader in buffer text
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    assert(len > 0);
    text = calloc(1, len + 1);
    assert(text != NULL);
    fseek(f, 0, SEEK_SET);
    fread(text, 1, len, f);
    assert(strlen(text) > 0);
    fclose(f);
    text[len] = '\0';

    if (out_len)
        *out_len = len;

    // return null terminated string
    return text;
}

static inline GLuint shader_compile_text(const char *text, size_t len, GLenum type)
{
    // create and compile shader
    const GLuint handle = glCreateShader(type);
    glShaderSource(handle, 1, (const GLchar *const *)&text, (const GLint *)&len);
    glCompileShader(handle);

    return handle;
}

static inline GLint shader_get_status(
    GLuint handle, GLenum pname,
    void (*getiv)(GLuint, GLenum, GLint *))
{
    GLint status = 0;
    getiv(handle, pname, &status);
    return status;
}

static inline void shader_log_status(
    GLuint handle, const char *prefix, const char *path_a, const char *path_b,
    void (*getlog)(GLuint, GLsizei, GLsizei *, GLchar *),
    void (*getiv)(GLuint, GLenum, GLint *))
{
    char *logtext = shader_get_log(handle, getlog, getiv);

    char path[VCP_MAX_STRING_LEN] = { 0 };
    if (path_a) snprintf(path, VCP_MAX_STRING_LEN, " [ %s ]", path_a);
    else if (path_b) snprintf(path, VCP_MAX_STRING_LEN, " [ %s, %s ]", path_a, path_b);

    // Log shader messages
    if (logtext)
    {
        log_trace("%s shader logs%s:\n%s", prefix, path, logtext);
    }

    free(logtext);
}

static inline GLuint shader_link_program(GLuint vs, GLuint fs)
{
    const GLuint handle = glCreateProgram();

    // Link shader program
    glAttachShader(handle, vs);
    glAttachShader(handle, fs);

    // note: must bind attributes before linking
    //// Bind vertex attributes
    //for (size_t i = 0; i < n; i++) {
    //	glBindAttribLocation(self.handle, attributes[i].index, attributes[i].name);
    //}

    glLinkProgram(handle);

    // we can detach and delete the shaders after we are done linking them
    glDetachShader(handle, vs);
    glDeleteShader(vs);

    glDetachShader(handle, fs);
    glDeleteShader(fs);

    return handle;
}

static inline int shader_build_text(struct Shader *self, const char *vstext, size_t vslen, const char *fstext, size_t fslen, const char *vspath, const char *fspath)
{
    *self = (struct Shader){ 0 };

    const GLuint vs_handle = shader_compile_text(vstext, vslen, GL_VERTEX_SHADER);
    const GLuint fs_handle = shader_compile_text(fstext, fslen, GL_FRAGMENT_SHADER);

    const GLint vs_status = shader_get_status(vs_handle, GL_COMPILE_STATUS, glGetShaderiv);
    const GLint fs_status = shader_get_status(fs_handle, GL_COMPILE_STATUS, glGetShaderiv);

    shader_log_status(vs_handle, "Vertex", vspath, NULL, glGetShaderInfoLog, glGetShaderiv);
    shader_log_status(fs_handle, "Fragment", fspath, NULL, glGetShaderInfoLog, glGetShaderiv);

    if (vs_status == GL_FALSE)
    {
        glDeleteShader(vs_handle);
        glDeleteShader(fs_handle);
        log_warn("Vertex Shader [ID:%d] %s failed to compile", vs_handle, vspath ? vspath : "");
        return SHADER_VS_COMPILE_ERROR;
    }
    log_info("Vertex Shader [ID:%d] %s compiled successfully", vs_handle, vspath ? vspath : "");

    if (fs_status == GL_FALSE)
    {
        glDeleteShader(vs_handle);
        glDeleteShader(fs_handle);
        log_warn("Fragment Shader [ID:%d] %s failed to compile", fs_handle, fspath ? fspath : "");
        return SHADER_FS_COMPILE_ERROR;
    }
    log_info("Fragment Shader [ID:%d] %s compiled successfully", fs_handle, fspath ? fspath : "");

    self->handle = shader_link_program(vs_handle, fs_handle);
    const GLint sp_status = shader_get_status(self->handle, GL_LINK_STATUS, glGetProgramiv);
    shader_log_status(self->handle, "Program", vspath, fspath, glGetProgramInfoLog, glGetProgramiv);

    if (sp_status == GL_FALSE)
    {
        glDeleteProgram(self->handle);
        log_warn("Shader Program [ID:%d|VS:%d|FS:%d] failed to link", self->handle, vs_handle, fs_handle);
        return SHADER_PROGRAM_LINKING_ERROR;
    }
    log_info("Shader Program [ID:%d|VS:%d|FS:%d] successfully loaded", self->handle, vs_handle, fs_handle);

    glUseProgram(self->handle);
    return SHADER_SUCCESS;
}

struct Shader shader_load(const char *vstext, const char *fstext)
{
    struct Shader result = { 0 };
    result.status = shader_build_text(&result, vstext, strlen(vstext), fstext, strlen(fstext), NULL, NULL);
    return result;
}

struct Shader shader_loadf(const char *vspath, const char *fspath)
{
    struct Shader result = { 0 };
    size_t vslen = 0;
    size_t fslen = 0;
    char *vstext = shader_load_text(vspath, &vslen);
    char *fstext = shader_load_text(fspath, &fslen);

    if (!vstext || !fstext)
    {
        result.status = SHADER_INVALID_FILE_PATH;
        return result;
    }

    result.status = shader_build_text(&result, vstext, vslen, fstext, fslen, vspath, fspath);

    free(vstext);
    free(fstext);

    return result;
}

void shader_free(struct Shader self)
{
    glDeleteProgram(self.handle);
}

void shader_bind(struct Shader self)
{
    glUseProgram(self.handle);
}

void shader_uniform_mat4(struct Shader self, const char *name, struct Mat4 m)
{
    const GLint idx = glGetUniformLocation(self.handle, name);
    if (idx < 0) log_warn("Unable to uniform variable: %s", name);
    glUniformMatrix4fv(idx, 1, GL_FALSE, mat4_flatten(m).m);
}

void shader_uniform_float(struct Shader self, const char *name, float f)
{
    const GLint idx = glGetUniformLocation(self.handle, name);
    if (idx < 0) log_warn("Unable to uniform variable: %s", name);
    glUniform1f(idx, f);
}

void shader_uniform_vec2(struct Shader self, const char *name, struct Vec2 v)
{
    const GLint idx = glGetUniformLocation(self.handle, name);
    if (idx < 0) log_warn("Unable to uniform variable: %s", name);
    glUniform2f(idx, v.x, v.y);
}

void shader_uniform_vec3(struct Shader self, const char *name, struct Vec3 v)
{
    const GLint idx = glGetUniformLocation(self.handle, name);
    if (idx < 0) log_warn("Unable to uniform variable: %s", name);
    glUniform3f(idx, v.x, v.y, v.z);
}

void shader_uniform_vec4(struct Shader self, const char *name, struct Vec4 v)
{
    const GLint idx = glGetUniformLocation(self.handle, name);
    if (idx < 0) log_warn("Unable to uniform variable: %s", name);
    glUniform4f(idx, v.x, v.y, v.z, v.w);
}

void shader_uniform_int(struct Shader self, const char *name, int v)
{
    const GLint idx = glGetUniformLocation(self.handle, name);
    if (idx < 0) log_warn("Unable to uniform variable: %s", name);
    glUniform1i(idx, v);
}

void shader_uniform_uint(struct Shader self, const char *name, unsigned int v)
{
    const GLint idx = glGetUniformLocation(self.handle, name);
    if (idx < 0) log_warn("Unable to uniform variable: %s", name);
    glUniform1ui(idx, v);
}
