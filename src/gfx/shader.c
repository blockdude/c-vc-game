#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <util/log.h>

static GLint shader_compile_( const char *path, GLenum type )
{
	FILE *f;
	char *text;
	long len;

	f = fopen( path, "rb" );
	if ( f == NULL ) {
		log_error( "Error loading shader at %s", path );
		return -1;
	}

	fseek( f, 0, SEEK_END );
	len = ftell( f );
	assert( len > 0 );
	fseek( f, 0, SEEK_SET );
	text = calloc( 1, len );
	assert( text != NULL );
	fread( text, 1, len, f );
	assert( strlen( text ) > 0 );
	fclose( f );

	GLuint handle = glCreateShader( type );
	glShaderSource( handle, 1, ( const GLchar *const * ) &text, ( const GLint * ) &len );
	glCompileShader( handle );

	GLint compiled;
	glGetShaderiv( handle, GL_COMPILE_STATUS, &compiled );

	// Check OpenGL logs if compilation failed
	if ( compiled == 0 )
	{
		log_error( "Error compiling shader at %s", path );
		return -1;
	}

	free(text);
	return handle;
}

struct shader shader_load( const char *vs, const char *fs )
{
	struct shader self;

	self.vs_handle = shader_compile_( vs, GL_VERTEX_SHADER );
	self.fs_handle = shader_compile_( fs, GL_FRAGMENT_SHADER );
	self.handle = glCreateProgram();

	// Link shader program
	glAttachShader( self.handle, self.vs_handle );
	glAttachShader( self.handle, self.fs_handle );

	//// Bind vertex attributes
	//for (size_t i = 0; i < n; i++) {
	//	glBindAttribLocation(self.handle, attributes[i].index, attributes[i].name);
	//}

	glLinkProgram( self.handle );

	// Check link status
	GLint linked;
	glGetProgramiv( self.handle, GL_LINK_STATUS, &linked );

	if ( linked == 0 ) {
		log_error( "Error linking shader at [ %s, %s ]", vs, fs );
		shader_free( self );
	}

	return self;
}

void shader_free( struct shader self )
{
	glDeleteProgram( self.handle );
	glDeleteShader( self.vs_handle );
	glDeleteShader( self.fs_handle );
}

void shader_bind( struct shader self )
{
	glUseProgram( self.handle );
}
