#include "vbo.h"

struct vbo vbo_create( GLint type, bool dyn )
{
	struct vbo self = {
		.type = type,
		.dyn = dyn
	};
	glGenBuffers( 1, &self.handle );
	return self;
}

void vbo_free( struct vbo self )
{
	glDeleteBuffers( 1, &self.handle );
}

void vbo_bind( struct vbo self )
{
	glBindBuffer( self.type, self.handle );
}

void vbo_buff( struct vbo self, void *data, size_t n )
{
	vbo_bind( self );
	glBufferData( self.type, n, data, self.dyn ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW );
}
