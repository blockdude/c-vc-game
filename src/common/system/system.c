#include "system.h"
#include "global.h"
#include "timestep.h"

#include <util/log.h>
#include <SDL3/SDL.h>
#include <glad/gl.h>

/*
 * =============================
 * -----------------------------
 * GLOBAL
 * -----------------------------
 */

struct core core = {
    .window.initialized = false,
    .window.flags       = 0,
    .window.title       = "Application",
    .window.width       = 700,
    .window.height      = 700,
    .window.aspect      = 1.0f,

    .input              = { 0 },
    .timer              = { 0 },
    .audio              = { 0 }
};

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * TIMESTEP
 * -----------------------------
 */

struct timestep __loop_local;
struct timestep *__loop = &__loop_local;

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * SYSTEM
 * -----------------------------
 */

struct platform
{
    SDL_Window *window;
    SDL_GLContext context;
} platform = { 0 };

void sys_init( unsigned int flags )
{
    core.flags = flags;

	log_info( "SDL Version : %d.%d.%d",
			SDL_VERSIONNUM_MAJOR( SDL_VERSION ),
			SDL_VERSIONNUM_MINOR( SDL_VERSION ),
			SDL_VERSIONNUM_MICRO( SDL_VERSION ) );

    if ( ( flags & TIMER ) > 0 )
    {
        sys_timer_init();
    }

    if ( ( flags & INPUT ) > 0 )
    {
        sys_input_init();
    }

    if ( ( flags & AUDIO ) > 0 )
    {
        sys_audio_init();
    }

    if ( ( flags & WINDOW ) > 0 )
    {
        sys_window_init();
    }
}

void sys_free( void )
{
    if ( platform.context )
    {
        SDL_GL_DestroyContext( platform.context );
        log_info( "Destroyed OpenGL context" );
    }

    if ( platform.window )
    {
        SDL_DestroyWindow( platform.window );
        log_info( "Destroyed SDL window" );
    }

    SDL_Quit();
    log_info( "Cleaned up SDL subsystems" );

    platform.window = NULL;
    platform.context = NULL;

    core.window.initialized = false;
    core.input.initialized  = false;
    core.timer.initialized  = false;
    core.audio.initialized  = false;
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * AUDIO
 * -----------------------------
 */

void sys_audio_init( void )
{
    if ( SDL_Init( SDL_INIT_AUDIO ) != 0 )
    {
        log_warn( "Unable to initialize SDL audio system: %s", SDL_GetError() );
        return;
    }

    core.audio.initialized = true;
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * INPUT
 * -----------------------------
 */

void sys_input_init( void )
{
    if ( SDL_Init( SDL_INIT_EVENTS ) != 0 )
    {
        log_warn( "Unable to initialize SDL event system: %s", SDL_GetError() );
        return;
    }

    core.input.initialized = true;
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * TIME
 * -----------------------------
 */

void sys_timer_init( void )
{
    if ( SDL_Init( SDL_INIT_TIMER ) != 0 )
    {
        log_warn( "Unable to initialize SDL timer system: %s", SDL_GetError() );
        return;
    }

    core.timer.initialized = true;
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * WINDOW
 * -----------------------------
 */

void sys_window_init( void )
{
    if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        log_warn( "Unable to initialize SDL video system: %s", SDL_GetError() );
        goto cleanup;
    }

    const SDL_WindowFlags flags =
        SDL_WINDOW_RESIZABLE          |
        SDL_WINDOW_HIGH_PIXEL_DENSITY |
        SDL_WINDOW_OPENGL;

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 6 );
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );

    platform.window = SDL_CreateWindow( core.window.title, core.window.width, core.window.height, flags );
    if ( platform.window == NULL )
    {
        log_warn( "Failed to initialize system. Unable to create SDL window: %s", SDL_GetError() );
        goto cleanup;
    }

    platform.context = SDL_GL_CreateContext( platform.window );
    if ( platform.context == NULL )
    {
        log_warn( "Failed to initialize system. Unable to create OpenGL context: %s", SDL_GetError() );
        goto cleanup;
    }

    int loaded = gladLoadGL( ( GLADloadfunc ) SDL_GL_GetProcAddress );
    if ( loaded == 0 )
    {
        log_warn( "Failed to load opengl functions" );
        goto cleanup;
    }

    log_info( "Vendor      : %s", glGetString( GL_VENDOR ) );
    log_info( "Renderer    : %s", glGetString( GL_RENDERER ) );
    log_info( "GL Version  : %s", glGetString( GL_VERSION ) );
    log_info( "SL Version  : %s", glGetString( GL_SHADING_LANGUAGE_VERSION ) );
    goto finalize;

cleanup:
    if ( platform.context )
        SDL_GL_DestroyContext( platform.context );

    if ( platform.window )
        SDL_DestroyWindow( platform.window );

    platform.window = NULL;
    platform.context = NULL;

    goto exit;

finalize:
    core.window.initialized = true;

exit:;
}

void *sys_window_handle( void )
{
    return platform.window;
}

/*
 * =============================
 */
