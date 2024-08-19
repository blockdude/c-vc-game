#include "input.h"
#include <util/util.h>

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
        // mouse wheel delta
        float x;
        float y;
    } wheel;

    struct {
        // relative mouse position
        float x;
        float y;

        // mouse delta
        float dx;
        float dy;

        // global mouse position
        float gx;
        float gy;
    } pos;

    bool moved;
};

struct input
{
    struct key_state key[ INPUT_KB_COUNT ];
    struct mouse_state mouse;

    resize_cb_fn *resize_cb;
    quit_cb_fn *quit_cb;
};

static struct input input = {
    .key        = { 0 },
    .mouse      = { 0 },
    .resize_cb  = NULL,
    .quit_cb    = NULL
};

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
    input.mouse.pos.dx = 0;
    input.mouse.pos.dy = 0;
}

int input_poll( void )
{
    input_reset();

    int result = INPUT_SUCCESS;

    SDL_Event event;
    while ( SDL_PollEvent( &event ) )
    {
        switch ( event.type )
        {
            case SDL_EVENT_QUIT:
                {
                    size_t len = list_size( input.quit_cb );
                    for ( size_t i = 0; i < len; i++ )
                        input.quit_cb[ i ]();
                    result = INPUT_QUIT;
                }
                break;

            case SDL_EVENT_WINDOW_RESIZED:
                {
                    size_t len = list_size( input.resize_cb );
                    for ( size_t i = 0; i < len; i++ )
                        input.resize_cb[ i ]( event.window.data1, event.window.data2 );
                }
                break;

            case SDL_EVENT_KEY_DOWN:

                key_down( &input.key[ event.key.scancode ] );

                break;

            case SDL_EVENT_KEY_UP:

                key_up( &input.key[ event.key.scancode ] );

                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:

                key_down( &input.mouse.button[ button_from_sdl( event.button.button ) ] );

                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:

                key_up( &input.mouse.button[ button_from_sdl( event.button.button ) ] );

                break;

            case SDL_EVENT_MOUSE_WHEEL:

                input.mouse.wheel.x += event.wheel.x;
                input.mouse.wheel.y += event.wheel.y;

                break;

            case SDL_EVENT_MOUSE_MOTION:

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

int input_resize_add_listener( resize_cb_fn fn )
{
    list_push_back( input.resize_cb, fn );
    return INPUT_SUCCESS;
}

int input_quit_add_listener( quit_cb_fn fn )
{
    list_push_back( input.quit_cb, fn );
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

void input_mouse_pos( float *x, float *y )
{
    if ( x ) *x = input.mouse.pos.x;
    if ( y ) *y = input.mouse.pos.y;
}

void input_mouse_delta( float *x, float *y )
{
    if ( x ) *x = input.mouse.pos.dx;
    if ( y ) *y = input.mouse.pos.dy;
}

void input_mouse_scroll( float *x, float *y )
{
    if ( x ) *x = input.mouse.wheel.x;
    if ( y ) *y = input.mouse.wheel.y;
}
