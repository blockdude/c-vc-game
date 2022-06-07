#include "input.h"

static const u8 *key_state;
static bool key_state_down = false;
static bool key_state_up = false;

static bool mouse_state_down = false;
static bool mouse_state_up = false;
static bool mouse_state_move = false;
static s32 mouse_state_scroll = 0;

void input_init()
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

void input_update()
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

bool key_down( enum Key key )
{
    return key_state_down && key_state[ key ];
}

bool key_up( enum Key key )
{
    return key_state_up && key_state[ key ];
}

bool key_press( enum Key key )
{
    return key_state[ key ];
}

bool mouse_down( enum Button button )
{
    u32 mouse_state = SDL_GetMouseState( NULL, NULL );
    return mouse_state_down && ( mouse_state & button );
}

bool mouse_up( enum Button button )
{
    u32 mouse_state = SDL_GetMouseState( NULL, NULL );
    return mouse_state_up && ( mouse_state & button );
}

bool mouse_press( enum Button button )
{
    u32 mouse_state = SDL_GetMouseState( NULL, NULL );
    return mouse_state & button;
}

bool mouse_move()
{
    return mouse_state_move;
}

void mouse_pos( int *x, int *y )
{
    SDL_GetMouseState( x, y );
}

s32 mouse_scroll()
{
    return mouse_state_scroll;
}
