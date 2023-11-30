#include "game.h"
#include "state.h"

#include <util/util.h>
#include <gfx/window.h>
#include <gfx/render.h>
#include <system/input.h>
#include <gfx/shader.h>
#include <gfx/obj3d.h>
#include <gfx/vbo.h>
#include <gfx/vao.h>
#include <gfx/camera.h>

#include <cglm/cglm.h>
#include <glad/glad.h>

#include <stdio.h>

static struct shader shader;
static struct obj3d obj;
static struct camera camera;

static float scale;

static struct vao vao;
static struct vbo vbo;
static GLuint scale_idx, center_idx, aspect_idx;

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
    vao = vao_create();
    vao_bind( vao );

    // create and bind our vbo
    vbo = vbo_create( GL_ARRAY_BUFFER, false );
    vbo_bind( vbo );

    // upload data to our gpu
    vbo_buff( vbo, obj.f, obj.f_nbytes );

    GLuint pos_idx = glGetAttribLocation( shader.handle, "position" );
    GLuint norm_idx = glGetAttribLocation( shader.handle, "normal" );

    vao_attr(
        vao, vbo,
        pos_idx,
        obj.v_nval,
        GL_FLOAT,
        obj.stride,
        obj.v_offset
    );

    vao_attr(
        vao, vbo,
        norm_idx,
        obj.vn_nval,
        GL_FLOAT,
        obj.stride,
        obj.vn_offset
    );
    
    // Configure uniform variables.
    scale_idx = glGetUniformLocation( shader.handle, "scale" );
    center_idx = glGetUniformLocation( shader.handle, "center" );
    aspect_idx = glGetUniformLocation( shader.handle, "aspect" );

    log_debug( "Uniform locations: %d, %d, %d, %d, %d", scale_idx, center_idx, aspect_idx, pos_idx, norm_idx );
    log_debug( "Object vertices: %d", obj.f_len );
    
    // init rendering details
    scale = 2.0f / obj.dia;

    // set uniform variables
    glUniform1f( scale_idx, scale );
    glUniform1f( aspect_idx, window.aspect );
    glUniform3f( center_idx, obj.center.x, obj.center.y, obj.center.z );

    return 0;
}

int game_free( void )
{
    vbo_free( vbo );
    vao_free( vao );
    shader_free( shader );
    obj3d_free( &obj );
    return 0;
}

int game_tick( void )
{
    return 0;
}

int game_update( void )
{
    glUniform1f( aspect_idx, window.aspect );
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
