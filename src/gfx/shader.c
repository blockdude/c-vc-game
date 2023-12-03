#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <util/log.h>
#include <glad/glad.h>

static inline char *shader_get_log_( 
		GLint handle,
		void ( *getlog )( GLuint, GLsizei, GLsizei *, GLchar * ),
		void ( *getiv )( GLuint, GLenum, GLint * ) )
{
	GLint loglen;
	getiv( handle, GL_INFO_LOG_LENGTH, &loglen );

	if ( loglen <= 1 )
		return NULL;

	char *logtext = malloc( loglen * sizeof( *logtext ) );
	getlog( handle, loglen, NULL, logtext );

	return logtext;
}

static char *shader_load_text_( const char *path, size_t *out_len )
{
	FILE *f;
	char *text;
	size_t len;

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

	if ( out_len )
		*out_len = len;

	return text;
}

static GLint shader_compile_text_( const char *text, size_t len, GLenum type )
{
	// create and compile shader
	GLuint handle = glCreateShader( type );
	glShaderSource( handle, 1, ( const GLchar *const * ) &text, ( const GLint * ) &len );
	glCompileShader( handle );

	return handle;
}

static int shader_log_status_(
		GLuint handle, GLenum pname,
		const char *adverb, const char *vspath, const char *fspath,
		void ( *getlog )( GLuint, GLsizei, GLsizei *, GLchar * ),
		void ( *getiv )( GLuint, GLenum, GLint * ) )
{
	int result = 0;

	GLint status;
	getiv( handle, pname, &status );
	char *logtext = shader_get_log_( handle, getlog, getiv );

	char path[ 512 ];
	if      ( vspath == NULL ) snprintf( path, 512, "[ %s ]", fspath );
	else if ( fspath == NULL ) snprintf( path, 512, "[ %s ]", vspath );
	else                       snprintf( path, 512, "[ %s, %s ]", vspath, fspath );

	// Check OpenGL logs if compilation failed
	if ( status == 0 )
	{
		log_error( "Error %s shader at %s:\n%s", adverb, path, logtext );
		result = 1;
	}
	else if ( logtext )
	{
		log_trace( "Warning %s shader at %s:\n%s", adverb, path, logtext );
	}

	free( logtext );

	return result;
}

GLuint shader_link_program_( GLuint vs, GLuint fs )
{
	GLuint handle = glCreateProgram();

	// Link shader program
	glAttachShader( handle, vs );
	glAttachShader( handle, fs );

	// note: must bind attributes before linking
	//// Bind vertex attributes
	//for (size_t i = 0; i < n; i++) {
	//	glBindAttribLocation(self.handle, attributes[i].index, attributes[i].name);
	//}

	glLinkProgram( handle );
	return handle;
}

int shader_load( struct shader *self, const char *vspath, const char *fspath )
{
	if ( self == NULL )
		return 1;

	*self = ( struct shader ){ 0 };

	size_t vslen;
	size_t fslen;

	char *vstext = shader_load_text_( vspath, &vslen );
	char *fstext = shader_load_text_( fspath, &fslen );

	self->vs_handle = shader_compile_text_( vstext, vslen, GL_VERTEX_SHADER );
	self->fs_handle = shader_compile_text_( fstext, fslen, GL_FRAGMENT_SHADER );

	int vsstatus = shader_log_status_( self->vs_handle, GL_COMPILE_STATUS, "compiling", vspath, NULL, glGetShaderInfoLog, glGetShaderiv );
	int fsstatus = shader_log_status_( self->fs_handle, GL_COMPILE_STATUS, "compiling", fspath, NULL, glGetShaderInfoLog, glGetShaderiv );

	free( vstext );
	free( fstext );

	if ( vsstatus != 0 || fsstatus != 0 )
	{
		glDeleteShader( self->vs_handle );
		glDeleteShader( self->fs_handle );
		return 2;
	}

	self->handle = shader_link_program_( self->vs_handle, self->fs_handle );
	int spstatus = shader_log_status_( self->handle, GL_LINK_STATUS, "linking", fspath, NULL, glGetProgramInfoLog, glGetProgramiv );
	if ( spstatus != 0 )
	{
		glDeleteProgram( self->handle );
		glDeleteShader( self->vs_handle );
		glDeleteShader( self->fs_handle );
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

void shader_uniform_mat4( struct shader self, char *name, mat4s m )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
    glUniformMatrix4fv( idx, 1, GL_FALSE, ( const GLfloat * )&m.raw );
}

void shader_uniform_float( struct shader self, char *name, float f )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
    glUniform1f( idx, f );
}

void shader_uniform_vec2( struct shader self, char *name, vec2s v )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
    glUniform2f( idx, v.x, v.y );
}

void shader_uniform_vec3( struct shader self, char *name, vec3s v )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
    glUniform3f( idx, v.x, v.y, v.z );
}

void shader_uniform_vec4( struct shader self, char *name, vec4s v )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
    glUniform4f( idx, v.x, v.y, v.z, v.w );
}

void shader_uniform_int( struct shader self, char *name, int v )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
    glUniform1i( idx, v );
}

void shader_uniform_uint( struct shader self, char *name, unsigned int v )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
    glUniform1ui( idx, v );
}
