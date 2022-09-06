#include "input.h"

static const u8 *key_state;
static bool key_state_down = false;
static bool key_state_up = false;

static bool mouse_state_down = false;
static bool mouse_state_up = false;
static bool mouse_state_move = false;
static i32 mouse_state_scroll = 0;

void input_init( void )
{
    key_state = SDL_GetKeyboardState( NULL );
}

void input_handle( SDL_Event *event )
{
    switch ( event->type )
    {
        // get key state
        case SDL_KEYDOWN:

            key_state_down = true;

            break;

        case SDL_KEYUP:

            key_state_up = true;

            break;

        // get mouse state
        case SDL_MOUSEBUTTONDOWN:

            mouse_state_down = true;

            break;

        case SDL_MOUSEBUTTONUP:

            mouse_state_up = true;

            break;

        case SDL_MOUSEWHEEL:

            mouse_state_scroll = event->wheel.y;

            break;

        case SDL_MOUSEMOTION:

            mouse_state_move = true;

            break;
    }
}

void input_update( void )
{
    // reset key state
    key_state_down = false;
    key_state_up = false;
    
    // reset mouse state
    mouse_state_down = false;
    mouse_state_up = false;
    mouse_state_move = false;
    mouse_state_scroll = 0;
}

bool key_down( enum keyboard input )
{
    return key_state_down && key_state[ input ];
}

bool key_up( enum keyboard input )
{
    return key_state_up && key_state[ input ];
}

bool key_press( enum keyboard input )
{
    return key_state[ input ];
}

bool mouse_down( enum mouse input )
{
    u32 mouse_state = SDL_GetMouseState( NULL, NULL );
    return mouse_state_down && ( mouse_state & input );
}

bool mouse_up( enum mouse input )
{
    u32 mouse_state = SDL_GetMouseState( NULL, NULL );
    return mouse_state_up && ( mouse_state & input );
}

bool mouse_press( enum mouse input )
{
    u32 mouse_state = SDL_GetMouseState( NULL, NULL );
    return mouse_state & input;
}

bool mouse_move( void )
{
    return mouse_state_move;
}

void mouse_pos( int *x, int *y )
{
    SDL_GetMouseState( x, y );
}

i32 mouse_scroll( void )
{
    return mouse_state_scroll;
}
