#include <string>

#include <util/log.h>
#include <system/system.h>
#include <glad/glad.h>
#include <system/app.h>
#include <cglm/struct.h>
#include <util/list.h>
#include <util/math.h>
#include <util/list.h>
#include <gfx/gfx.h>

static const GLfloat square[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
     1.0f,  1.0f,

     1.0f,  1.0f,
    -1.0f,  1.0f,
    -1.0f, -1.0f
};

static struct shader shader;
static struct vao vao;
static struct vbo vbo;
static int state_idx;

#define SIZE 128

static int buff_a[ SIZE * SIZE ];
static int buff_b[ SIZE * SIZE ];
static int *out = buff_a;
static int *buf = buff_b;

static int init( struct app *app )
{
	( void )app;
	app_set_target_fps( app, 0 );
	app_set_target_tps( app, 30 );
	SDL_GL_SetSwapInterval( 0 );

	glEnable( GL_DEPTH_TEST );

	if ( shader_loadf( &shader, "res/shaders/instancing.vert", "res/shaders/simple.frag" ) != 0 )
		exit( 1 );

	shader_bind( shader );
	state_idx = glGetUniformLocation( shader.handle, "state" );


	vao = vao_create();
	vao_bind( vao );
	vbo = vbo_create( GL_ARRAY_BUFFER, false );
	vbo_bind( vbo );
	vbo_buff( vbo, ( void * ) square, sizeof( square ) );
	int position_i = glGetAttribLocation( shader.handle, "position" );
	vao_attr( vao, vbo, position_i, 2, GL_FLOAT, 0, 0 );

	// randomize our grid
	for (int i = 0; i < SIZE * SIZE; i++)
		buf[ i ] = ( rand() % 2 ) == 0 ? 1 : buf[ i ];

	return 0;
}

static int free( struct app *app )
{
	( void )app;
	vbo_free( vbo );
	vao_free( vao );
	shader_free( shader );
	return 0;
}

static int tick( struct app *app )
{
	( void )app;

	std::string s = std::to_string( app->frame_rate ) + " | " + std::to_string( app->tick_rate );
	window_set_title( s.c_str() );

	return 0;
}

static int update( struct app *app )
{
	( void ) app;

	// update alive state
	for ( int i = 0; i < SIZE * SIZE; i++ )
	{
		out[ i ] = buf[ i ];

		int x = i % SIZE;			// column
		int y = ( i - x ) / SIZE;	// row

		// wrap around left right
		int l = ( x - 1 ) < 0 ? SIZE - 1 : x - 1;
		int r = ( x + 1 ) % SIZE;

		// wrap around above below
		int a = ( y - 1 ) < 0 ? SIZE - 1 : y - 1;
		int b = ( y + 1 ) % SIZE;

		int neighbors =
			// get above
			buf[ a * SIZE + l ] +
			buf[ a * SIZE + x ] +
			buf[ a * SIZE + r ] +
			// get middle
			buf[ y * SIZE + l ] +
			buf[ y * SIZE + r ] +
			// get below
			buf[ b * SIZE + l ] +
			buf[ b * SIZE + x ] +
			buf[ b * SIZE + r ];

		// cell rules
		if ( neighbors >= 4 || neighbors <= 1 )
			out[ i ] = 0;
		else if ( neighbors == 3 )
			out[ i ] = 1;
	}

	//swap buffers
	int *tmp = out;
	out = buf;
	buf = tmp;


	return 0;
}

static int render( struct app *app )
{
	( void )app;
	glClearColor( 1.f, 1.f, 1.f, 1.f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glUniform1iv(state_idx, SIZE * SIZE, out );
	glDrawArraysInstanced( GL_TRIANGLES, 0, 6, SIZE * SIZE );

	SDL_GL_SwapWindow( window.handle );

	return 0;
}
