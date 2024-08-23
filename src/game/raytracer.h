#include <util/math.h>
#include <util/log.h>
#include <system/input.h>
#include <system/app.h>
#include <gfx/gfx.h>

#include <cglm/cglm.h>
#include <cglm/struct.h>
#include <glad/glad.h>

#include "../../res/shaders/raytracer/vert.h"
#include "../../res/shaders/raytracer/frag.h"
#include "SDL3/SDL_video.h"
#include "gfx/window.h"

#include <string>

/* ================================== */
/* obj stuff */
/* ================================== */
static struct camera camera;
static vec3_t light_pos   = { 0.0f, 5.0f, 0.0f };
static vec3_t light_color = { 1.0f, 1.0f, 1.0f };
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
static float speed      = 10.0f;
static float mouse_sens = 0.0009f;
static float fov        = 45.0f;
/* ================================== */

/* ================================== */
/* screen update */
/* ================================== */
static const GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f
};
/* ================================== */

int init( struct app *app )
{
    ( void ) app;
	app_set_target_fps( app, 0 );
	app_set_target_tps( app, 60 );
	SDL_GL_SetSwapInterval( 1 );

    glEnable( GL_DEPTH_TEST );

    log_info( "Loading and compiling shaders..." );
    if ( shader_load( &shader, ( char * )vert_glsl, vert_glsl_len, ( char * )frag_glsl, frag_glsl_len ) != 0 )
    {
        log_error( "Failed to build shaders" );
		exit( 1 );
    }

    shader_bind( shader );

    // create and bind our vao
    vao = vao_create();
    vao_bind( vao );

    // create and bind our vbo
    vbo = vbo_create( GL_ARRAY_BUFFER, false );
    vbo_bind( vbo );

    // upload data to our gpu
    vbo_buff( vbo, ( void * )vertices, sizeof( vertices ) );

    // set vao attributes
    GLuint pos_idx = glGetAttribLocation( shader.handle, "position" );
    vao_attr( vao, vbo, pos_idx, 3, GL_FLOAT, 0, 0 );
    
    // init rendering details
    camera_init( &camera, DEGTORAD( fov ) );
    camera.pitch = DEGTORAD( 0 );
    camera.yaw   = DEGTORAD( 0 );

    // uniform objects to fragment shader
    shader_uniform_vec3( shader, "plane.pos",  { 0.0f, -1.0f, 0.0f } );
    shader_uniform_vec3( shader, "plane.norm", { 0.0f,  1.0f, 0.0f } );

    shader_uniform_vec3( shader,  "lights[0].pos",    light_pos );
    shader_uniform_vec3( shader,  "lights[0].color",  light_color );
    shader_uniform_float( shader, "lights[0].radius", 1.0f );
    shader_uniform_float( shader, "lights[0].reach",  300.0f );
    shader_uniform_float( shader, "lights[0].power",  1.0f );

    shader_uniform_uint( shader,  "objects[0].type", 1 );
    shader_uniform_vec3( shader,  "objects[0].pos", { 3.0f, 0.0f, 0.0f } );
    shader_uniform_float( shader, "objects[0].scale", 1.0f );
    shader_uniform_vec3( shader,  "objects[0].mat.color", { 0.0f, 1.0f, 0.0f } );
    shader_uniform_float( shader, "objects[0].mat.reflectiveness", 0.0f );

    shader_uniform_uint( shader,  "objects[1].type", 1 );
    shader_uniform_vec3( shader,  "objects[1].pos", { 0.0f, 0.0f, 0.0f } );
    shader_uniform_float( shader, "objects[1].scale", 1.0f );
    shader_uniform_vec3( shader,  "objects[1].mat.color", { 0.0f, 0.0f, 1.0f } );
    shader_uniform_float( shader, "objects[1].mat.reflectiveness", 1.0f );

    shader_uniform_uint( shader,  "objects[2].type", 1 );
    shader_uniform_vec3( shader,  "objects[2].pos", { -3.0f, 0.0f, 0.0f } );
    shader_uniform_float( shader, "objects[2].scale", 1.0f );
    shader_uniform_vec3( shader,  "objects[2].mat.color", { 1.0f, 0.0f, 0.0f } );
    shader_uniform_float( shader, "objects[2].mat.reflectiveness", 0.5f );

    shader_uniform_uint( shader,  "objects[3].type", 1 );
    shader_uniform_vec3( shader,  "objects[3].pos", { 0.0f, 0.0f, 3.0f } );
    shader_uniform_float( shader, "objects[3].scale", 1.0f );
    shader_uniform_vec3( shader,  "objects[3].mat.color", { 1.0f, 1.0f, 1.0f } );
    shader_uniform_float( shader, "objects[3].mat.reflectiveness", 0.8f );

    shader_uniform_uint( shader,  "objects[4].type", 1 );
    shader_uniform_vec3( shader,  "objects[4].pos", { 0.0f, 0.0f, -3.0f } );
    shader_uniform_float( shader, "objects[4].scale", 1.0f );
    shader_uniform_vec3( shader,  "objects[4].mat.color", { 0.8f, 0.8f, 0.8f } );
    shader_uniform_float( shader, "objects[4].mat.reflectiveness", 0.08f );

    window_set_relative_mouse( true );

    return 0;
}

int free( struct app *app )
{
    ( void ) app;
    vbo_free( vbo );
    vao_free( vao );
    shader_free( shader );
    return 0;
}

int tick( struct app *app )
{
    ( void ) app;
	std::string s = std::to_string( app->frame_rate ) + " | " + std::to_string( app->tick_rate );
	window_set_title( s.c_str() );
    return 0;
}

int update( struct app *app )
{
    ( void ) app;

    /* ======================================================== */
    /* --------------------------- */
    /* CHARACTER MOVEMENT		   */
    /* --------------------------- */

    vec3_t direction = { 0, 0, 0 };
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

    if ( input_mouse_moved() )
    {
        float dx, dy;
        input_mouse_delta( &dx, &dy );
        camera.yaw   -= dx * mouse_sens;
        camera.pitch -= dy * mouse_sens;
    }

    if ( input_key_down( INPUT_KB_ESCAPE ) )
    {
        window_toggle_relative_mouse();
    }

    direction = vec3_scale( direction, speed * app->frame_delta );
    camera.eye = vec3_add( camera.eye, direction );
    camera.aspect = window.aspect;
    camera_update( &camera );

    shader_uniform_vec3( shader, "camera.eye", camera.eye );
    shader_uniform_mat4( shader, "camera.view", camera.view );
    shader_uniform_float( shader, "camera.fov", camera.fov );

    /* ======================================================== */

    /* ======================================================== */
    /* --------------------------- */
    /* LIGHT MOVEMENT		       */
    /* --------------------------- */

    direction.x = 0;
    direction.y = 0;
    direction.z = 0;
    if ( input_key_press( INPUT_KB_LEFT ) )
    {
        direction.x += 1;
    }

    if ( input_key_press( INPUT_KB_RIGHT ) )
    {
        direction.x -= 1;
    }

    if ( input_key_press( INPUT_KB_UP ) )
    {
        direction.z += 1;
    }

    if ( input_key_press( INPUT_KB_DOWN ) )
    {
        direction.z -= 1;
    }

    direction = vec3_scale( direction, speed * app->frame_delta );
    light_pos = vec3_add( light_pos, direction );
    shader_uniform_vec3( shader,  "lights[0].pos", light_pos );

    /* ======================================================== */

    /* ======================================================== */
    /* --------------------------- */
    /* LIGHT PROFILES		       */
    /* --------------------------- */

    if ( input_key_down( INPUT_KB_1 ) )
    {
        shader_uniform_vec3( shader, "lights[0].color", light_color );
    }

    if ( input_key_down( INPUT_KB_2 ) )
    {
        shader_uniform_vec3( shader, "lights[0].color", { 0.4f, 0.9f, 1.0f } );
    }

    if ( input_key_down( INPUT_KB_3 ) )
    {
        shader_uniform_vec3( shader, "lights[0].color", { 1.0f, 0.2f, 1.0f } );
    }

    if ( input_key_down( INPUT_KB_4 ) )
    {
        shader_uniform_vec3( shader, "lights[0].color", { 0.7f, 0.6f, 0.2f } );
    }

    if ( input_key_down( INPUT_KB_5 ) )
    {
        shader_uniform_vec3( shader, "lights[0].color", { 0.8f, 0.7f, 0.8f } );
    }

    if ( input_key_down( INPUT_KB_6 ) )
    {
        shader_uniform_float( shader, "lights[0].reach",  300.0f );
        shader_uniform_float( shader, "lights[0].power",  1.0f );
    }

    if ( input_key_down( INPUT_KB_7 ) )
    {
        shader_uniform_float( shader, "lights[0].reach",  30.0f );
        shader_uniform_float( shader, "lights[0].power",  0.8f );
    }

    if ( input_key_down( INPUT_KB_8 ) )
    {
        shader_uniform_float( shader, "lights[0].reach",  10.0f );
        shader_uniform_float( shader, "lights[0].power",  0.5f );
    }

    if ( input_key_down( INPUT_KB_9 ) )
    {
        shader_uniform_float( shader, "lights[0].reach",  7.0f );
        shader_uniform_float( shader, "lights[0].power",  0.3f );
    }

    /* ======================================================== */

    shader_uniform_vec2( shader, "resolution", { ( float )window.w, ( float )window.h } );

    return 0;
}

int render( struct app *app )
{
    ( void ) app;
    glClearColor( 1.f, 1.f, 1.f, 1.f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glDrawArrays( GL_TRIANGLES, 0, 6 );
    SDL_GL_SwapWindow( window.handle );

    return 0;
}
