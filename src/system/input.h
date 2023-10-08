#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define INPUT_SUCCESS 0
#define INPUT_QUIT 1
#define INPUT_ERROR -1

// keyboard buton input
enum input_key
{
    INPUT_KB_FIRST            = 0,

    INPUT_KB_UNKNOWN          = SDL_SCANCODE_UNKNOWN,

    INPUT_KB_A                = SDL_SCANCODE_A,
    INPUT_KB_B                = SDL_SCANCODE_B,
    INPUT_KB_C                = SDL_SCANCODE_C,
    INPUT_KB_D                = SDL_SCANCODE_D,
    INPUT_KB_E                = SDL_SCANCODE_E,
    INPUT_KB_F                = SDL_SCANCODE_F,
    INPUT_KB_G                = SDL_SCANCODE_G,
    INPUT_KB_H                = SDL_SCANCODE_H,
    INPUT_KB_I                = SDL_SCANCODE_I,
    INPUT_KB_J                = SDL_SCANCODE_J,
    INPUT_KB_K                = SDL_SCANCODE_K,
    INPUT_KB_L                = SDL_SCANCODE_L,
    INPUT_KB_M                = SDL_SCANCODE_M,
    INPUT_KB_N                = SDL_SCANCODE_N,
    INPUT_KB_O                = SDL_SCANCODE_O,
    INPUT_KB_P                = SDL_SCANCODE_P,
    INPUT_KB_Q                = SDL_SCANCODE_Q,
    INPUT_KB_R                = SDL_SCANCODE_R,
    INPUT_KB_S                = SDL_SCANCODE_S,
    INPUT_KB_T                = SDL_SCANCODE_T,
    INPUT_KB_U                = SDL_SCANCODE_U,
    INPUT_KB_V                = SDL_SCANCODE_V,
    INPUT_KB_W                = SDL_SCANCODE_W,
    INPUT_KB_X                = SDL_SCANCODE_X,
    INPUT_KB_Y                = SDL_SCANCODE_Y,
    INPUT_KB_Z                = SDL_SCANCODE_Z,

    INPUT_KB_0                = SDL_SCANCODE_0,
    INPUT_KB_1                = SDL_SCANCODE_1,
    INPUT_KB_2                = SDL_SCANCODE_2,
    INPUT_KB_3                = SDL_SCANCODE_3,
    INPUT_KB_4                = SDL_SCANCODE_4,
    INPUT_KB_5                = SDL_SCANCODE_5,
    INPUT_KB_6                = SDL_SCANCODE_6,
    INPUT_KB_7                = SDL_SCANCODE_7,
    INPUT_KB_8                = SDL_SCANCODE_8,
    INPUT_KB_9                = SDL_SCANCODE_9,

    INPUT_KB_RETURN           = SDL_SCANCODE_RETURN,
    INPUT_KB_ESCAPE           = SDL_SCANCODE_ESCAPE,
    INPUT_KB_BACKSPACE        = SDL_SCANCODE_BACKSPACE,
    INPUT_KB_TAB              = SDL_SCANCODE_TAB,
    INPUT_KB_SPACE            = SDL_SCANCODE_SPACE,

    INPUT_KB_MINUS            = SDL_SCANCODE_MINUS,
    INPUT_KB_EQUAL            = SDL_SCANCODE_EQUALS,
    INPUT_KB_LEFT_BRACKET     = SDL_SCANCODE_LEFTBRACKET,
    INPUT_KB_RIGHT_BRACKET    = SDL_SCANCODE_RIGHTBRACKET,
    INPUT_KB_BACKSLASH        = SDL_SCANCODE_BACKSLASH,

    INPUT_KB_RIGHT            = SDL_SCANCODE_RIGHT,
    INPUT_KB_LEFT             = SDL_SCANCODE_LEFT,
    INPUT_KB_DOWN             = SDL_SCANCODE_DOWN,
    INPUT_KB_UP               = SDL_SCANCODE_UP,
    INPUT_KB_LEFT_CTRL        = SDL_SCANCODE_LCTRL,
    INPUT_KB_LEFT_ALT         = SDL_SCANCODE_LALT,
    INPUT_KB_LEFT_SHIFT       = SDL_SCANCODE_LSHIFT,
    INPUT_KB_RIGHT_CTRL       = SDL_SCANCODE_RCTRL,
    INPUT_KB_RIGHT_ALT        = SDL_SCANCODE_RALT,
    INPUT_KB_RIGHT_SHIFT      = SDL_SCANCODE_RSHIFT,

    INPUT_KB_COUNT            = SDL_NUM_SCANCODES,
    INPUT_KB_LAST             = INPUT_KB_RIGHT_SHIFT
};

// mouse button input
enum input_button
{
    INPUT_MB_FIRST            = 0,

    INPUT_MB_LEFT             = 0,
    INPUT_MB_RIGHT            = 1,
    INPUT_MB_MIDDLE           = 2,
    INPUT_MB_XA               = 3,
    INPUT_MB_XB               = 4,

    INPUT_MB_COUNT,
    INPUT_MB_LAST             = INPUT_MB_COUNT - 1
};

// input stuff
int input_init( void );
int input_process_events( void );
int input_free( void );

bool input_key_down( enum input_key key );
bool input_key_up( enum input_key key );
bool input_key_press( enum input_key key );

bool input_mouse_down( enum input_button button );
bool input_mouse_up( enum input_button button );
bool input_mouse_press( enum input_button button );
bool input_mouse_moved( void );
void input_mouse_pos( int *x, int *y );
void input_mouse_pos_delta( int *x, int *y );
void input_mouse_scroll( int *x, int *y );
void input_mouse_fscroll( float *x, float *y );

#endif
