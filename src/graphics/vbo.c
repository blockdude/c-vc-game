#include <vcp/vcp.h>

struct VBO vbo_create(GLint type, bool dyn)
{
    struct VBO self = {
        .type = type,
        .dyn = dyn
    };

    glGenBuffers(1, &self.handle);
    glBindBuffer(self.type, self.handle);
    return self;
}

void vbo_free(struct VBO self)
{
    glDeleteBuffers(1, &self.handle);
}

void vbo_bind(struct VBO self)
{
    glBindBuffer(self.type, self.handle);
}

void vbo_buff(struct VBO self, const void *data, size_t n)
{
    vbo_bind(self);
    glBufferData(self.type, n, data, self.dyn ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}
