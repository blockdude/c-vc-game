#include "game.h"
#include "state.h"
#include <gfx/window.h>
#include <gfx/render.h>
#include <util/util.h>
#include <system/input.h>
#include <glad/glad.h>
#include <gfx/shader.h>
#include <gfx/obj3d.h>
#include <stdio.h>
#include <cglm/cglm.h>

static struct shader shader;
static struct obj3d obj;

static float scale;

static GLuint vao, vbo;
static GLuint scale_loc, center_loc, aspect_loc;

int game_init( void )
{
    glEnable( GL_DEPTH_TEST );

    shader = shader_load( "res/shaders/vert.glsl", "res/shaders/frag.glsl" );
    shader_bind( shader );

    int res = obj3d_load( &obj, "res/objects/rayman.obj" );

    if ( res != 0 )
    {
        log_error( "Failed to load object..." );
        return -1;
    }

    // create and bind our vao
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // create and bind our vbo
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );

    // upload data to our gpu
    glBufferData(
            GL_ARRAY_BUFFER,
            obj.f_nbytes,
            obj.f,
            GL_STATIC_DRAW
    );

    GLuint position_loc = glGetAttribLocation( shader.handle, "position" );
    GLuint normal_loc = glGetAttribLocation( shader.handle, "normal" );

    glVertexAttribPointer(
        position_loc,       // Now we specify how the data is stored in the VBO for the position attribute
        obj.v_nval,         // Specify the number of components per attribute: 3 for position (x, y, z)
        GL_FLOAT,           // Specify the type of the components
        GL_FALSE,           // Specify if we want the data to be normalized
        obj.stride,         // Specify the stride (number of bytes between each vertex)
        obj.v_offset_ptr    // Specify the starting point (in bytes) for the position data
    );
    
    glVertexAttribPointer(
        normal_loc,         // Now we specify how the data is stored in the VBO for the position attribute
        obj.vn_nval,        // Specify the number of components per attribute: 3 for position (x, y, z)
        GL_FLOAT,           // Specify the type of the components
        GL_FALSE,           // Specify if we want the data to be normalized
        obj.stride,         // Specify the stride (number of bytes between each vertex)
        obj.vn_offset_ptr   // Specify the starting point (in bytes) for the position data
    );
    
    // mark attribute as being used
    glEnableVertexAttribArray( position_loc );
    glEnableVertexAttribArray( normal_loc );
    
    // Configure uniform variables.
    scale_loc = glGetUniformLocation( shader.handle, "scale" );
    center_loc = glGetUniformLocation( shader.handle, "center" );
    aspect_loc = glGetUniformLocation( shader.handle, "aspect" );

    log_debug( "Uniform locations: %d, %d, %d, %d, %d", scale_loc, center_loc, aspect_loc, position_loc, normal_loc );
    log_debug( "Object vertices: %d", obj.f_len );
    
    // init rendering details
    scale = 2.0f / obj.dia;

    // set uniform variables
    glUniform1f( scale_loc, scale );
    glUniform1f( aspect_loc, window.aspect );
    glUniform3f( center_loc, obj.center.x, obj.center.y, obj.center.z );

    return 0;
}

int game_free( void )
{
    glDeleteBuffers( 1, &vbo );
    glDeleteVertexArrays( 1, &vao );

    shader_free( shader );
    obj3d_free( &obj );
    return 0;
}

int game_tick( void )
{
    mat4 m = {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    };

    glm_translate(m, (vec3){1.0f, 0.0f, 0.0f});
    return 0;
}

int game_update( void )
{
    glUniform1f( aspect_loc, window.aspect );
    return 0;
}

int game_render( void )
{
    glClearColor( 1.f, 1.f, 1.f, 1.f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glDrawArrays(
            GL_TRIANGLES,
            0,
            obj.f_len
    );

    char buff[ 256 ];
    sprintf( buff, "frame : %5lu | fps : %u | tick : %5lu | tps : %u", window.frame.count, window.frame.rate, window.tick.count, window.tick.rate );
    window_set_title( buff );

    return 0;
}
