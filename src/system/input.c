#include "input.h"
#include "../util/util.h"

struct key_state
{
    // true when button is down ( lasts one frame )
    bool down;

    // true when button is up ( lasts one frame )
    bool up;

    // true when while button is held down
    bool press;

    // true when key is double pressed lasts one frame
    bool repeat;
};

struct mouse_state
{
    struct key_state button[ INPUT_MB_COUNT ];

    struct {
        // integer wheel delta
        int x;
        int y;

        // float wheel delta
        float fx;
        float fy;
    } wheel;

    struct {
        // position relative to window
        int x;
        int y;

        // delta x and y
        int dx;
        int dy;

        // global position
        int gx;
        int gy;
    } pos;

    bool moved;
};

struct input
{
    struct key_state key[ INPUT_KB_COUNT ];
    struct mouse_state mouse;

    input_resize_callback_fn resize_cb;
    input_quit_callback_fn quit_cb;
};

static struct input input;

static enum input_button button_from_sdl( Uint8 sdlbutton )
{
    switch ( sdlbutton )
    {
        case SDL_BUTTON_LEFT: return INPUT_MB_LEFT;
        case SDL_BUTTON_RIGHT: return INPUT_MB_RIGHT;
        case SDL_BUTTON_MIDDLE: return INPUT_MB_MIDDLE;
        case SDL_BUTTON_X1: return INPUT_MB_XA;
        case SDL_BUTTON_X2: return INPUT_MB_XB;
    }

    return INPUT_MB_FIRST;
}

static void key_up( struct key_state *state )
{
    state->up = state->press;
    state->press = false;
}

static void key_down( struct key_state *state )
{
    state->down = !state->press;
    state->press = true;
}

static void key_update( struct key_state *state )
{
    state->down = false;
    state->up = false;
}

static void input_reset( void )
{
    // reset keys
    for ( int i = 0; i < INPUT_KB_COUNT; i++ )
        key_update( &input.key[ i ] );

    // reset mouse buttons
    for ( int i = 0; i < INPUT_MB_COUNT; i++ )
        key_update( &input.mouse.button[ i ] );

    // reset mouse events
    input.mouse.moved = false;
    input.mouse.wheel.x = 0;
    input.mouse.wheel.y = 0;
    input.mouse.wheel.fx = 0;
    input.mouse.wheel.fy = 0;
    input.mouse.pos.dx = 0;
    input.mouse.pos.dy = 0;
}

int input_init( void )
{
    input.resize_cb = NULL;
    input.quit_cb = NULL;
    return INPUT_SUCCESS;
}

int input_process_events( void )
{
    input_reset();

    int result = INPUT_SUCCESS;

    SDL_Event event;
    while ( SDL_PollEvent( &event ) )
    {
        switch ( event.type )
        {
            case SDL_QUIT:

                if ( input.quit_cb ) input.quit_cb();
                result = INPUT_QUIT;

                break;

            case SDL_WINDOWEVENT:

                switch ( event.window.event )
                {
                    case SDL_WINDOWEVENT_RESIZED:
                    case SDL_WINDOWEVENT_SIZE_CHANGED:

                        if ( input.resize_cb ) input.resize_cb( event.window.data1, event.window.data2 );

                        break;
                }

                break;

            case SDL_KEYDOWN:

                key_down( &input.key[ event.key.keysym.scancode ] );

                break;

            case SDL_KEYUP:

                key_up( &input.key[ event.key.keysym.scancode ] );

                break;

            case SDL_MOUSEBUTTONDOWN:

                key_down( &input.mouse.button[ button_from_sdl( event.button.button ) ] );

                break;

            case SDL_MOUSEBUTTONUP:

                key_up( &input.mouse.button[ button_from_sdl( event.button.button ) ] );

                break;

            case SDL_MOUSEWHEEL:

                input.mouse.wheel.x += event.wheel.x;
                input.mouse.wheel.y += event.wheel.y;
                input.mouse.wheel.fx += event.wheel.preciseX;
                input.mouse.wheel.fy += event.wheel.preciseY;

                break;

            case SDL_MOUSEMOTION:

                input.mouse.pos.x = event.motion.x;
                input.mouse.pos.y = event.motion.y;
                input.mouse.pos.dx += event.motion.xrel;
                input.mouse.pos.dy += event.motion.yrel;
                input.mouse.moved = true;

                break;
        }
    }

    return result;
}

int input_set_resize_callback( input_resize_callback_fn fn )
{
    input.resize_cb = fn;
    return INPUT_SUCCESS;
}

int input_set_quit_callback( input_quit_callback_fn fn )
{
    input.quit_cb = fn;
    return INPUT_SUCCESS;
}

int input_free( void )
{
    return INPUT_SUCCESS;
}

bool input_key_down( enum input_key key )
{
    return input.key[ key ].down;
}

bool input_key_up( enum input_key key )
{
    return input.key[ key ].up;
}

bool input_key_press( enum input_key key )
{
    return input.key[ key ].press;
}

bool input_mouse_down( enum input_button button )
{
    return input.mouse.button[ button ].down;
}

bool input_mouse_up( enum input_button button )
{
    return input.mouse.button[ button ].up;
}

bool input_mouse_press( enum input_button button )
{
    return input.mouse.button[ button ].press;
}

bool input_mouse_moved( void )
{
    return input.mouse.moved;
}

void input_mouse_pos( int *x, int *y )
{
    if ( x ) *x = input.mouse.pos.x;
    if ( y ) *y = input.mouse.pos.y;
}

void input_mouse_pos_delta( int *x, int *y )
{
    if ( x ) *x = input.mouse.pos.dx;
    if ( y ) *y = input.mouse.pos.dy;
}

void input_mouse_scroll( int *x, int *y )
{
    if ( x ) *x = input.mouse.wheel.x;
    if ( y ) *y = input.mouse.wheel.y;
}

void input_mouse_fscroll( float *x, float *y )
{
    if ( x ) *x = input.mouse.wheel.fx;
    if ( y ) *y = input.mouse.wheel.fy;
}
