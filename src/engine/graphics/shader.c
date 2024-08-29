#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <util/log.h>
#include <util/math.h>
#include <glad/glad.h>

static inline char *shader_get_log( 
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

static char *shader_load_text( const char *path, size_t *out_len )
{
	FILE *f;
	char *text;
	size_t len;

	f = fopen( path, "rb" );
	if ( f == NULL )
	{
		log_warn( "Could not open shader file: %s", path );
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

static inline GLuint shader_compile_text( const char *text, size_t len, GLenum type )
{
	// create and compile shader
	GLuint handle = glCreateShader( type );
	glShaderSource( handle, 1, ( const GLchar *const * ) &text, ( const GLint * ) &len );
	glCompileShader( handle );

	return handle;
}

static inline GLint shader_get_status(
		GLuint handle, GLenum pname,
		void ( *getiv )( GLuint, GLenum, GLint * ) )
{
	GLint status;
	getiv( handle, pname, &status );
	return status;
}

static inline void shader_log_status(
		GLuint handle, const char *prefix, const char *path_a, const char *path_b,
		void ( *getlog )( GLuint, GLsizei, GLsizei *, GLchar * ),
		void ( *getiv )( GLuint, GLenum, GLint * ) )
{
	char *logtext = shader_get_log( handle, getlog, getiv );

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

static inline GLuint shader_link_program( GLuint vs, GLuint fs )
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

	// we can detach and delete the shaders after we are done linking them
	glDetachShader( handle, vs );
	glDeleteShader( vs );

	glDetachShader( handle, fs );
	glDeleteShader( fs );

	return handle;
}

static inline int shader_build_text( struct shader *self, const char *vstext, size_t vslen, const char *fstext, size_t fslen, const char *vspath, const char *fspath )
{
	*self = ( struct shader ) { 0 };

	GLuint vs_handle = shader_compile_text( vstext, vslen, GL_VERTEX_SHADER );
	GLuint fs_handle = shader_compile_text( fstext, fslen, GL_FRAGMENT_SHADER );

	GLint vs_status = shader_get_status( vs_handle, GL_COMPILE_STATUS, glGetShaderiv );
	GLint fs_status = shader_get_status( fs_handle, GL_COMPILE_STATUS, glGetShaderiv );
	
	shader_log_status( vs_handle, "Vertex"  , vspath, NULL, glGetShaderInfoLog, glGetShaderiv );
	shader_log_status( fs_handle, "Fragment", fspath, NULL, glGetShaderInfoLog, glGetShaderiv );

	if ( vs_status == GL_FALSE )
	{
		glDeleteShader( vs_handle );
		glDeleteShader( fs_handle );
		log_warn( "Vertex shader [ ID: %d ] failed to compile" );
		return SHADER_VS_COMPILE_ERROR;
	}
	log_info( "Vertex shader [ ID: %d ] compiled successfully", vs_handle );

	if ( fs_status == GL_FALSE )
	{
		glDeleteShader( vs_handle );
		glDeleteShader( fs_handle );
		log_warn( "Fragment shader [ ID: %d ] failed to compile" );
		return SHADER_FS_COMPILE_ERROR;
	}
	log_info( "Fragment shader [ ID: %d ] compiled successfully", fs_handle );

	self->handle = shader_link_program( vs_handle, fs_handle );
	GLint sp_status = shader_get_status( self->handle, GL_LINK_STATUS, glGetProgramiv );
	shader_log_status( self->handle, "Program", vspath, fspath, glGetProgramInfoLog, glGetProgramiv );

	if ( sp_status == GL_FALSE )
	{
		glDeleteProgram( self->handle );
		log_warn( "Program shader [ ID: %d ] failed to link", self->handle );
		return SHADER_PROGRAM_LINKING_ERROR;
	}
	log_info( "Program shader [ ID: %d ] successfully loaded", self->handle );

	return SHADER_SUCCESS;
}

int shader_load( struct shader *self, const char *vstext, size_t vslen, const char *fstext, size_t fslen )
{
	if ( self == NULL )
		return SHADER_SUCCESS;

	return shader_build_text( self, vstext, vslen, fstext, fslen, NULL, NULL );
}

int shader_loadf( struct shader *self, const char *vspath, const char *fspath )
{
	if ( self == NULL )
		return SHADER_SUCCESS;

	size_t vslen;
	size_t fslen;
	char *vstext = shader_load_text( vspath, &vslen );
	char *fstext = shader_load_text( fspath, &fslen );

	if ( !vstext || !fstext )
		return SHADER_INVALID_FILE_PATH;

	int result = shader_build_text( self, vstext, vslen, fstext, fslen, vspath, fspath );

	free( vstext );
	free( fstext );

	return result;
}

void shader_free( struct shader self )
{
	glDeleteProgram( self.handle );
}

void shader_bind( struct shader self )
{
	glUseProgram( self.handle );
}

void shader_uniform_mat4( struct shader self, const char *name, mat4_t m )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
    glUniformMatrix4fv( idx, 1, GL_FALSE, mat4_to_float( m ) );
}

void shader_uniform_float( struct shader self, const char *name, float f )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
    glUniform1f( idx, f );
}

void shader_uniform_vec2( struct shader self, const char *name, vec2_t v )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
	glUniform2f( idx, v.x, v.y );
}

void shader_uniform_vec3( struct shader self, const char *name, vec3_t v )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
	glUniform3f( idx, v.x, v.y, v.z );
}

void shader_uniform_vec4( struct shader self, const char *name, vec4_t v )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
	glUniform4f( idx, v.x, v.y, v.z, v.w );
}

void shader_uniform_int( struct shader self, const char *name, int v )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
    glUniform1i( idx, v );
}

void shader_uniform_uint( struct shader self, const char *name, unsigned int v )
{
	GLint idx = glGetUniformLocation( self.handle, name );
	if ( idx < 0 ) log_warn( "Unable to uniform variable: %s", name );
    glUniform1ui( idx, v );
}
