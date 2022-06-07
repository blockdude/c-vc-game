#ifndef INPUT_H
#define INPUT_H

#include "util.h"

// keyboard inputs
enum Key
{
    // movement
    KB_UP           = SDL_SCANCODE_W,
    KB_DOWN         = SDL_SCANCODE_S,
    KB_LEFT         = SDL_SCANCODE_A,
    KB_RIGHT        = SDL_SCANCODE_D,

    // second naming for movement because i cannot decide rn
    KB_NORTH        = SDL_SCANCODE_W,
    KB_SOUTH        = SDL_SCANCODE_S,
    KB_WEST         = SDL_SCANCODE_A,
    KB_EAST         = SDL_SCANCODE_D,

    // other
    KB_INTERACT     = SDL_SCANCODE_F,
    KB_DROP         = SDL_SCANCODE_Q,
    KB_ATTACK       = SDL_SCANCODE_SPACE,
    KD_ESC          = SDL_SCANCODE_ESCAPE
};

// mouse inputs
enum Button
{
    MB_LEFT         = SDL_BUTTON_LMASK,
    MB_RIGHT        = SDL_BUTTON_RMASK,
    MB_MIDDLE       = SDL_BUTTON_MMASK
};

// state handler (for main.c only)
void input_init();
void input_handle( SDL_Event *event );
void input_update();

// true when key has been pressed (lasts one frame)
bool key_down( enum Key key );

// true when key is released (lasts one frame)
bool key_up( enum Key key );

// true while key is held
bool key_press( enum Key key );


// true when button is pressed (lasts one frame)
bool mouse_down( enum Button button );

// true when button is released (lasts one frame)
bool mouse_up( enum Button button );

// true when button is held
bool mouse_press( enum Button button );

// true when mouse is moved
bool mouse_move();

// get mouse position on window
void mouse_pos( int *x, int *y );

// returns amount scrolled in a frame otherwise returns zero
s32 mouse_scroll();

#endif
