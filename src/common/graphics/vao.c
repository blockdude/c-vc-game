#include "vao.h"

struct vao vao_create( void )
{
	struct vao self;
	glGenVertexArrays( 1, &self.handle );
	glBindVertexArray( self.handle );
	return self;
}

void vao_free( struct vao self )
{
	glDeleteVertexArrays( 1, &self.handle );
}

void vao_bind( struct vao self )
{
	glBindVertexArray( self.handle );
}

void vao_attr( struct vao self, struct vbo vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset )
{
	vao_bind( self );
	vbo_bind( vbo );
	glVertexAttribPointer( index, size, type, GL_FALSE, stride, ( void * ) offset );
	glEnableVertexAttribArray( index );
}
