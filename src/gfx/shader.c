#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <util/log.h>

static void shader_log_error_(
		GLint handle, const char *adverb, const char *path,
		void ( *getlog )( GLuint, GLsizei, GLsizei *, GLchar * ),
		void ( *getiv )( GLuint, GLenum, GLint * ) )
{
	GLint loglen;
	getiv( handle, GL_INFO_LOG_LENGTH, &loglen );

	char *logtext = calloc( 1, loglen );
	getlog( handle, loglen, NULL, logtext );
	log_error( "Error %s shader at %s:\n%s", adverb, path, logtext );

	free( logtext );
}

static GLint shader_compile_( const char *path, GLenum type )
{
	FILE *f;
	char *text;
	long len;

	f = fopen( path, "rb" );
	if ( f == NULL )
	{
		log_error( "Error. Could not open shader file: %s", path );
		return 0;
	}

	// put shader in buffer text
	fseek( f, 0, SEEK_END );
	len = ftell( f );
	assert( len > 0 );
	text = calloc( 1, len );
	assert( text != NULL );
	fseek( f, 0, SEEK_SET );
	fread( text, 1, len, f );
	assert( strlen( text ) > 0 );
	fclose( f );

	// create and compile shader
	GLuint handle = glCreateShader( type );
	glShaderSource( handle, 1, ( const GLchar *const * ) &text, ( const GLint * ) &len );
	glCompileShader( handle );

	GLint compiled;
	glGetShaderiv( handle, GL_COMPILE_STATUS, &compiled );

	// Check OpenGL logs if compilation failed
	if ( compiled == 0 )
	{
		shader_log_error_( handle, "compiling", path, glGetShaderInfoLog, glGetShaderiv );
		glDeleteShader( handle );
		return 0;
	}

	free( text );
	return handle;
}

int shader_load( struct shader *self, const char *vs, const char *fs )
{
	if ( self == NULL )
		return 1;

	*self = ( struct shader ){ 0 };

	self->vs_handle = shader_compile_( vs, GL_VERTEX_SHADER );
	self->fs_handle = shader_compile_( fs, GL_FRAGMENT_SHADER );

	if ( self->vs_handle == 0 || self->fs_handle == 0 )
		return 2;

	self->handle = glCreateProgram();

	// Link shader program
	glAttachShader( self->handle, self->vs_handle );
	glAttachShader( self->handle, self->fs_handle );

	//// Bind vertex attributes
	//for (size_t i = 0; i < n; i++) {
	//	glBindAttribLocation(self.handle, attributes[i].index, attributes[i].name);
	//}

	glLinkProgram( self->handle );

	// Check link status
	GLint linked;
	glGetProgramiv( self->handle, GL_LINK_STATUS, &linked );

	if ( linked == 0 )
	{
		char buf[ 512 ];
		snprintf( buf, 512, "[ %s, %s ]", vs, fs );
		shader_log_error_( self->handle, "linking", buf, glGetProgramInfoLog, glGetProgramiv );
		shader_free( *self );
		return 3;
	}

	return 0;
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
