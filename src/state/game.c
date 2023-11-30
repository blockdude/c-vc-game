#include "game.h"
#include "cglm/struct/vec3.h"
#include "state.h"

#include <SDL2/SDL.h>
#include <util/util.h>
#include <system/input.h>
#include <gfx/window.h>
#include <gfx/render.h>
#include <gfx/shader.h>
#include <gfx/obj3d.h>
#include <gfx/vbo.h>
#include <gfx/vao.h>
#include <gfx/camera.h>

#include <cglm/cglm.h>
#include <glad/glad.h>

#include <stdio.h>

/* ================================== */
/* obj stuff */
/* ================================== */
static struct obj3d obj;
static struct camera camera;
static mat4s model_matrix;
/* ================================== */

/* ================================== */
/* gpu stuff */
/* ================================== */
static struct vao vao;
static struct vbo vbo;
/* ================================== */

/* ================================== */
/* shader */
/* ================================== */
static struct shader shader;
static GLuint proj_idx, view_idx, model_idx;
/* ================================== */

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
    proj_idx = glGetUniformLocation( shader.handle, "proj_matrix" );
    view_idx = glGetUniformLocation( shader.handle, "view_matrix" );
    model_idx = glGetUniformLocation( shader.handle, "model_matrix" );

    log_debug( "Uniform locations: %d, %d", pos_idx, norm_idx );
    log_debug( "Object vertices: %d", obj.f_len );
    
    // init rendering details
    model_matrix = GLMS_MAT4_IDENTITY;
    camera_init( &camera, degtorad( 45.0f ) );
    camera.eye   = glms_vec3_add( camera.eye, obj.center );
    camera.eye   = glms_vec3_add( camera.eye, ( vec3s ){{ 0, 0, obj.dia }} );
    camera.pitch = degtorad( 0 );
    camera.yaw   = degtorad( 180 );

    SDL_SetRelativeMouseMode( true );

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
    vec3s direction = { 0 };
    float speed = 20.0f;
    float sens = 1.0f;

    if ( input_key_press( INPUT_KB_W ) )
    {
        direction.x += sinf( camera.yaw );
        direction.z += cosf( camera.yaw );
    }

    if ( input_key_press( INPUT_KB_S ) )
    {
        direction.x -= sinf( camera.yaw );
        direction.z -= cosf( camera.yaw );
    }

    if ( input_key_press( INPUT_KB_A ) )
    {
        direction.x += cosf( camera.yaw );
        direction.z -= sinf( camera.yaw );
    }

    if ( input_key_press( INPUT_KB_D ) )
    {
        direction.x -= cosf( camera.yaw );
        direction.z += sinf( camera.yaw );
    }

    if ( input_key_press( INPUT_KB_SPACE ) )
    {
        direction.y += 1;
    }

    if ( input_key_press( INPUT_KB_LEFT_SHIFT ) )
    {
        direction.y -= 1;
    }

    if ( input_key_press( INPUT_KB_LEFT ) )
    {
        camera.yaw += sens * window.frame.delta;
    }

    if ( input_key_press( INPUT_KB_RIGHT ) )
    {
        camera.yaw -= sens * window.frame.delta;
    }

    if ( input_key_press( INPUT_KB_UP ) )
    {
        camera.pitch += sens * window.frame.delta;
    }

    if ( input_key_press( INPUT_KB_DOWN ) )
    {
        camera.pitch -= sens * window.frame.delta;
    }

    if ( input_mouse_moved() )
    {
        int dx, dy;
        input_mouse_delta( &dx, &dy );
        camera.yaw   -= ( float )dx * 0.002f;
        camera.pitch -= ( float )dy * 0.002f;
    }

    direction = glms_vec3_normalize( direction );
    camera.eye.x += direction.x * speed * window.frame.delta;
    camera.eye.y += direction.y * speed * window.frame.delta;
    camera.eye.z += direction.z * speed * window.frame.delta;

    camera.aspect = window.aspect;
    camera_update( &camera );

    glUniformMatrix4fv( view_idx, 1, GL_FALSE,  ( float * )&camera.view );
    glUniformMatrix4fv( proj_idx, 1, GL_FALSE,  ( float * )&camera.proj );
    glUniformMatrix4fv( model_idx, 1, GL_FALSE, ( float * )&model_matrix );
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
