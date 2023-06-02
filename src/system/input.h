#ifndef INPUT_H
#define INPUT_H

#include "../util/util.h"
#include <SDL2/SDL.h>

#define INPUT_SUCCESS 0
#define INPUT_ERROR -1

// keyboard buton input
enum keyboard
{
    // movement
    KB_NORTH        = SDL_SCANCODE_W,
    KB_SOUTH        = SDL_SCANCODE_S,
    KB_EAST         = SDL_SCANCODE_D,
    KB_WEST         = SDL_SCANCODE_A,

    KB_UP           = SDL_SCANCODE_Q,
    KB_DOWN         = SDL_SCANCODE_E,

    // other
    KB_INTERACT     = SDL_SCANCODE_F,
    KB_DROP         = SDL_SCANCODE_Q,
    KB_ATTACK       = SDL_SCANCODE_SPACE,
    KB_ESC          = SDL_SCANCODE_ESCAPE
};

// mouse button input
enum mouse
{
    MB_LEFT         = SDL_BUTTON_LMASK,
    MB_RIGHT        = SDL_BUTTON_RMASK,
    MB_MIDDLE       = SDL_BUTTON_MMASK
};
/*
struct key_state
{
    bool press;
    bool up;
    bool down;
};

struct mouse_scroll
{
    float x;
    float y;
};

struct mouse
{
    struct key_state left;
    struct key_state right;
    struct mouse_scroll scroll;
    bool move;
};

struct input
{
    char key[ 128 ];
    struct mouse mouse;
};
*/

// state handler (for window.c only)
int input_init( void );
int input_poll_events( void );
int input_reset( void );
int input_free( void );

// true when key has been pressed (lasts one frame)
bool input_key_down( enum keyboard input );

// true when key is released (lasts one frame)
bool input_key_up( enum keyboard input );

// true while key is held
bool input_key_press( enum keyboard input );


// true when button is pressed (lasts one frame)
bool input_mouse_down( enum mouse input );

// true when button is released (lasts one frame)
bool input_mouse_up( enum mouse input );

// true when button is held
bool input_mouse_press( enum mouse input );

// true when mouse is moved
bool input_mouse_move( void );

// get mouse position on window
void input_mouse_pos( int *x, int *y );

// returns amount scrolled in a frame otherwise returns zero
float input_mouse_scroll( void );

#endif
