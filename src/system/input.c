#include "input.h"
#include "../gfx/window.h"

static const uint8_t *key_state;
static bool key_state_down = false;
static bool key_state_up = false;

static bool mouse_state_down = false;
static bool mouse_state_up = false;
static bool mouse_state_move = false;
static float mouse_state_scroll = 0;

int input_init( void )
{
    key_state = SDL_GetKeyboardState( NULL );
    return INPUT_SUCCESS;
}

int input_poll_events( void )
{
    SDL_Event event;
    while ( SDL_PollEvent( &event ) )
    {
        switch ( event.type )
        {
            case SDL_QUIT:

                window.running = false;

                break;

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

                mouse_state_scroll = event.wheel.preciseY;

                break;

            case SDL_MOUSEMOTION:

                mouse_state_move = true;

                break;
        }
    }

    return INPUT_SUCCESS;
}

int input_reset( void )
{
    // reset key state
    key_state_down = false;
    key_state_up = false;
    
    // reset mouse state
    mouse_state_down = false;
    mouse_state_up = false;
    mouse_state_move = false;
    mouse_state_scroll = 0;

    return INPUT_SUCCESS;
}

int input_free( void )
{
}

bool input_key_down( enum keyboard input )
{
    return key_state_down && key_state[ input ];
}

bool input_key_up( enum keyboard input )
{
    return key_state_up && key_state[ input ];
}

bool input_key_press( enum keyboard input )
{
    return key_state[ input ];
}

bool input_mouse_down( enum mouse input )
{
    uint32_t mouse_state = SDL_GetMouseState( NULL, NULL );
    return mouse_state_down && ( mouse_state & input );
}

bool input_mouse_up( enum mouse input )
{
    uint32_t mouse_state = SDL_GetMouseState( NULL, NULL );
    return mouse_state_up && ( mouse_state & input );
}

bool input_mouse_press( enum mouse input )
{
    uint32_t mouse_state = SDL_GetMouseState( NULL, NULL );
    return mouse_state & input;
}

bool input_mouse_move( void )
{
    return mouse_state_move;
}

void input_mouse_pos( int *x, int *y )
{
    SDL_GetMouseState( x, y );
}

float input_mouse_scroll( void )
{
    return mouse_state_scroll;
}
