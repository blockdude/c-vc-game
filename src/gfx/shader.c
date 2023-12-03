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
		return NULL;
	}

	// put shader in buffer text
	fseek( f, 0, SEEK_END );
	len = ftell( f );
	assert( len > 0 );
	text = calloc( 1, len + 1 );
	assert( text != NULL );
	fseek( f, 0, SEEK_SET );
	fread( text, 1, len, f );
	assert( strlen( text ) > 0 );
	fclose( f );
	text[ len ] = '\0';

	if ( out_len )
		*out_len = len;

	// return null terminated string
	return text;
}

static inline GLuint shader_compile_text_( const char *text, size_t len, GLenum type )
{
	// create and compile shader
	GLuint handle = glCreateShader( type );
	glShaderSource( handle, 1, ( const GLchar *const * ) &text, ( const GLint * ) &len );
	glCompileShader( handle );

	return handle;
}

static inline GLint shader_get_status_(
		GLuint handle, GLenum pname,
		void ( *getiv )( GLuint, GLenum, GLint * ) )
{
	GLint status;
	getiv( handle, pname, &status );
	return status;
}

static inline void shader_log_status_(
		GLuint handle, const char *prefix, const char *path_a, const char *path_b,
		void ( *getlog )( GLuint, GLsizei, GLsizei *, GLchar * ),
		void ( *getiv )( GLuint, GLenum, GLint * ) )
{
	char *logtext = shader_get_log_( handle, getlog, getiv );

	char path[ 512 ] = { 0 };
	if      ( path_a ) snprintf( path, 512, " [ %s ]", path_a );
	else if ( path_b ) snprintf( path, 512, " [ %s, %s ]", path_a, path_b );

	// Log shader messages
	if ( logtext )
	{
		log_trace( "%s shader logs%s:\n%s", prefix, path, logtext );
	}

	free( logtext );
}

static inline GLuint shader_link_program_( GLuint vs, GLuint fs )
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

static inline int shader_build_util_( struct shader *self, const char *vstext, size_t vslen, const char *fstext, size_t fslen, const char *vspath, const char *fspath )
{
	if ( self == NULL )
		return 1;

	*self = ( struct shader ){ 0 };

	self->vs_handle = shader_compile_text_( vstext, vslen, GL_VERTEX_SHADER );
	self->fs_handle = shader_compile_text_( fstext, fslen, GL_FRAGMENT_SHADER );

	GLint vsstatus = shader_get_status_( self->vs_handle, GL_COMPILE_STATUS, glGetShaderiv );
	GLint fsstatus = shader_get_status_( self->fs_handle, GL_COMPILE_STATUS, glGetShaderiv );
	
	shader_log_status_( self->vs_handle, "Vertex"  , vspath, NULL, glGetShaderInfoLog, glGetShaderiv );
	shader_log_status_( self->fs_handle, "Fragment", fspath, NULL, glGetShaderInfoLog, glGetShaderiv );

	if ( vsstatus == GL_FALSE || fsstatus == GL_FALSE )
	{
		glDeleteShader( self->vs_handle );
		glDeleteShader( self->fs_handle );
		return 2;
	}

	self->handle = shader_link_program_( self->vs_handle, self->fs_handle );
	GLint spstatus = shader_get_status_( self->handle, GL_LINK_STATUS, glGetProgramiv );
	shader_log_status_( self->handle, "Program", vspath, fspath, glGetProgramInfoLog, glGetProgramiv );

	if ( spstatus == GL_FALSE )
	{
		glDeleteProgram( self->handle );
		glDeleteShader( self->vs_handle );
		glDeleteShader( self->fs_handle );
		return 3;
	}

	return 0;
}

int shader_tbuild( struct shader *self, const char *vstext, size_t vslen, const char *fstext, size_t fslen )
{
	return shader_build_util_( self, vstext, vslen, fstext, fslen, NULL, NULL );
}

int shader_fbuild( struct shader *self, const char *vspath, const char *fspath )
{
	size_t vslen;
	size_t fslen;
	char *vstext = shader_load_text_( vspath, &vslen );
	char *fstext = shader_load_text_( fspath, &fslen );

	if ( !vstext || !fstext )
		return 4;

	int result = shader_build_util_( self, vstext, vslen, fstext, fslen, vspath, fspath );

	free( vstext );
	free( fstext );

	return result;
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
