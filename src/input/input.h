#ifndef INPUT_H
#define INPUT_H

#include "../util/util.h"
#include <SDL2/SDL.h>

// keyboard buton input
enum keyboard
{
    // movement
    KB_NORTH        = SDL_SCANCODE_W,
    KB_SOUTH        = SDL_SCANCODE_S,
    KB_EAST         = SDL_SCANCODE_D,
    KB_WEST         = SDL_SCANCODE_A,

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

// state handler (for main.c only)
void input_init( void );
void input_handle( SDL_Event *event );
void input_update( void );

// true when key has been pressed (lasts one frame)
bool key_down( enum keyboard input );

// true when key is released (lasts one frame)
bool key_up( enum keyboard input );

// true while key is held
bool key_press( enum keyboard input );


// true when button is pressed (lasts one frame)
bool mouse_down( enum mouse input );

// true when button is released (lasts one frame)
bool mouse_up( enum mouse input );

// true when button is held
bool mouse_press( enum mouse input );

// true when mouse is moved
bool mouse_move( void );

// get mouse position on window
void mouse_pos( int *x, int *y );

// returns amount scrolled in a frame otherwise returns zero
i32 mouse_scroll( void );

#endif
