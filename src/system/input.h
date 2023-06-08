#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#define INPUT_SUCCESS 0
#define INPUT_ERROR -1

// keyboard buton input
enum key
{
    KB_FIRST            = 0,

    KB_UNKNOWN          = 0,

    KB_A                = 1,
    KB_B                = 2,
    KB_C                = 3,
    KB_D                = 4,
    KB_E                = 5,
    KB_F                = 6,
    KB_G                = 7,
    KB_H                = 8,
    KB_I                = 9,
    KB_J                = 10,
    KB_K                = 11,
    KB_L                = 12,
    KB_M                = 13,
    KB_N                = 14,
    KB_O                = 15,
    KB_P                = 16,
    KB_Q                = 17,
    KB_R                = 18,
    KB_S                = 19,
    KB_T                = 20,
    KB_U                = 21,
    KB_V                = 22,
    KB_W                = 23,
    KB_X                = 24,
    KB_Y                = 25,
    KB_Z                = 26,

    KB_0                = 27,
    KB_1                = 28,
    KB_2                = 29,
    KB_3                = 30,
    KB_4                = 31,
    KB_5                = 32,
    KB_6                = 33,
    KB_7                = 34,
    KB_8                = 35,
    KB_9                = 36,

    KB_RETURN           = 37,
    KB_ESCAPE           = 38,
    KB_BACKSPACE        = 39,
    KB_TAB              = 40,
    KB_SPACE            = 41,

    KB_MINUS            = 42,
    KB_EQUAL            = 43,
    KB_LEFT_BRACKET     = 44,
    KB_RIGHT_BRACKET    = 45,
    KB_BACKSLASH        = 46,

    KB_EXCLAIM          = 47,
    KB_DOUBLE_QUOTE     = 48,
    KB_HASH             = 49,
    KB_PERCENT          = 50,
    KB_DOLLAR           = 51,
    KB_AMPERSAND        = 52,
    KB_SINGLE_QUOTE     = 53,
    KB_LEFT_PAREN       = 54,
    KB_RIGHT_PAREN      = 55,
    KB_ASTERISK         = 56,
    KB_PLUS             = 57,
    KB_COMMA            = 58,
    KB_PERIOD           = 59,
    KB_SLASH            = 60,

    KB_COLON            = 61,
    KB_SEMICOLON        = 62,
    KB_LESS             = 63,
    KB_GREATER          = 64,
    KB_QUESTION         = 65,
    KB_AT               = 66,
    KB_CARET            = 67,
    KB_UNDERSCORE       = 68,
    KB_GRAVE_ACCENT     = 69,
    KB_APOSTROPHE       = 70,

    KB_DELETE           = 71,

    KB_RIGHT            = 72,
    KB_LEFT             = 73,
    KB_DOWN             = 74,
    KB_UP               = 75,
    KB_LEFT_CTRL        = 76,
    KB_LEFT_ALT         = 77,
    KB_LEFT_SHIFT       = 78,
    KB_RIGHT_CTRL       = 79,
    KB_RIGHT_ALT        = 80,
    KB_RIGHT_SHIFT      = 81,
    KB_INSERT           = 82,
    KB_HOME             = 83,
    KB_END              = 84,
    KB_PAGE_UP          = 85,
    KB_PAGE_DOWN        = 86,

    KB_COUNT,
    KB_LAST             = KB_COUNT - 1
};

// mouse button input
enum mouse
{
    MB_FIRST            = 0,

    MB_LEFT             = 0,
    MB_RIGHT            = 1,
    MB_MIDDLE           = 2,
    MB_ALT_A            = 3,
    MB_ALT_B            = 4,

    MB_COUNT,
    MB_LAST             = MB_COUNT - 1
};

struct key_state
{
    bool down;
    bool up;
    bool press;
};

struct mouse_vec
{
    float x;
    float y;
};

struct mouse_state
{
    struct {
        struct key_state left;
        struct key_state middle;
        struct key_state right;
        struct key_state alt_1;
        struct key_state alt_2;
    } button;

    struct mouse_vec scroll;

    struct {
        struct mouse_vec abs;
        struct mouse_vec rel;
    } pos;

    bool moved;
};

struct input
{
    struct key_state key[ KB_COUNT ];
    struct mouse_state mouse;
};

// input stuff
int input_init( void );
int input_poll_events( void );
int input_free( void );

// true when key has been pressed (lasts one frame)
bool input_key_down( enum key input );

// true when key is released (lasts one frame)
bool input_key_up( enum key input );

// true while key is held
bool input_key_press( enum key input );


// true when button is pressed (lasts one frame)
bool input_mouse_down( enum mouse input );

// true when button is released (lasts one frame)
bool input_mouse_up( enum mouse input );

// true when button is held
bool input_mouse_press( enum mouse input );

// true when mouse is moved (lasts one frame)
bool input_mouse_move( void );

// get mouse position on window
void input_mouse_pos( int *x, int *y );

// returns amount scrolled in a frame otherwise returns zero
float input_mouse_scroll( void );

#endif
