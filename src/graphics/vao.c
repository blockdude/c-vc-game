#include "vao.h"

struct vao vao_create( void )
{
	struct vao self = { 0 };
	glGenVertexArrays( 1, &self.handle );
	glBindVertexArray( self.handle );
	return self;
}

void vao_free( struct vao self )
{
	glDeleteVertexArrays( 1, &self.handle );
}

void vao_bind( const struct vao self )
{
	glBindVertexArray( self.handle );
}

void vao_attr( const struct vao self, const struct vbo vbo, const GLuint index, const GLint size, const GLenum type, const GLsizei stride, const size_t offset )
{
	vao_bind( self );
	vbo_bind( vbo );
	glVertexAttribPointer( index, size, type, GL_FALSE, stride, ( void * ) offset );
	glEnableVertexAttribArray( index );
}
