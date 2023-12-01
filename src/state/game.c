#include "game.h"
#include "cglm/struct/mat4.h"
#include "cglm/struct/vec3.h"
#include "state.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
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
/* ================================== */

/* ================================== */
/* controls */
/* ================================== */
static vec3s direction  = { 0 };
static float speed      = 25.0f;
static float mouse_sens = 0.0009f;
/* ================================== */

int game_init( void )
{
    glEnable( GL_DEPTH_TEST );

    log_info( "Loading object file..." );
    if ( obj3d_load( &obj, "res/objects/cube.obj" ) != 0 )
    {
        log_error( "Failed to load object..." );
        return WINDOW_EXIT;
    }

    log_info( "Loading and compiling shaders..." );
    if ( shader_load( &shader, "res/shaders/raytracer/vert.glsl", "res/shaders/raytracer/frag.glsl" ) != 0 )
    {
        return WINDOW_EXIT;
    }

    shader_bind( shader );

    // create and bind our vao
    vao = vao_create();
    vao_bind( vao );

    // create and bind our vbo
    vbo = vbo_create( GL_ARRAY_BUFFER, false );
    vbo_bind( vbo );

    // upload data to our gpu
    vbo_buff( vbo, obj.fv, obj.fv_nbytes );

    GLuint pos_idx = glGetAttribLocation( shader.handle, "position" );
    GLuint norm_idx = glGetAttribLocation( shader.handle, "normal" );

    vao_attr(
        vao, vbo,
        pos_idx,
        obj.vp_nval,
        GL_FLOAT,
        obj.stride,
        obj.vp_offset
    );

    vao_attr(
        vao, vbo,
        norm_idx,
        obj.vn_nval,
        GL_FLOAT,
        obj.stride,
        obj.vn_offset
    );

    log_debug( "Object fv count: %d", obj.fv_len );
    log_debug( "Object vp count: %d", obj.vp_len );
    log_debug( "Object vt count: %d", obj.vt_len );
    log_debug( "Object vn count: %d", obj.vn_len );
    
    // init rendering details
    model_matrix = GLMS_MAT4_IDENTITY;
    camera_init( &camera, degtorad( 200.0f ) );
    //camera.eye   = glms_vec3_add( camera.eye, obj.center );
    //camera.eye   = glms_vec3_add( camera.eye, ( vec3s ){{ 0, 0, obj.dia }} );
    camera.pitch = degtorad( 0 );
    camera.yaw   = degtorad( 0 );

    window_set_relative_mouse( true );

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

    float sens = 1.0f;

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
        camera.yaw   -= ( float )dx * mouse_sens;
        camera.pitch -= ( float )dy * mouse_sens;
    }

    if ( input_key_down( INPUT_KB_ESCAPE ) )
    {
        window_toggle_relative_mouse();
    }

    direction = glms_vec3_scale( direction, speed * window.frame.delta );
    camera.eye = glms_vec3_add( camera.eye, direction );
    camera.aspect = window.aspect;

    direction = GLMS_VEC3_ZERO;
    camera_update( &camera );

    shader_uniform_mat4( shader, "view_matrix", camera.view );
    shader_uniform_mat4( shader, "proj_matrix", camera.proj );
    shader_uniform_mat4( shader, "model_matrix", model_matrix );

    shader_uniform_vec3( shader, "camera.eye", camera.eye );
    shader_uniform_vec3( shader, "camera.target", camera.target );
    shader_uniform_vec3( shader, "camera.up", camera.up );
    shader_uniform_mat4( shader, "camera.view", camera.view );

    shader_uniform_vec2( shader, "resolution", ( vec2s ){{ window.w, window.h }} );

    log_debug( "%f, %f, %f", camera.target.x, camera.target.y, camera.target.z );

    return 0;
}

int game_render( void )
{
    glClearColor( 1.f, 1.f, 1.f, 1.f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glDrawArrays(
            GL_TRIANGLES,
            0,
            obj.fv_len
    );

    char buff[ 256 ];
    sprintf( buff, "frame : %5lu | fps : %u | tick : %5lu | tps : %u", window.frame.count, window.frame.rate, window.tick.count, window.tick.rate );
    window_set_title( buff );

    return 0;
}
