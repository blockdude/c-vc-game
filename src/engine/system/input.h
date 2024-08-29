#ifndef INPUT_H
#define INPUT_H

#include <util/types.h>

enum input_status
{
    INPUT_ERROR   = -1,
    INPUT_SUCCESS =  0,
    INPUT_QUIT    =  1
};

// keyboard button input
enum input_key
{
    KB_FIRST      = 0,

    KB_NONE       = 0,

    KB_A          = 4,
    KB_B          = 5,
    KB_C          = 6,
    KB_D          = 7,
    KB_E          = 8,
    KB_F          = 9,
    KB_G          = 10,
    KB_H          = 11,
    KB_I          = 12,
    KB_J          = 13,
    KB_K          = 14,
    KB_L          = 15,
    KB_M          = 16,
    KB_N          = 17,
    KB_O          = 18,
    KB_P          = 19,
    KB_Q          = 20,
    KB_R          = 21,
    KB_S          = 22,
    KB_T          = 23,
    KB_U          = 24,
    KB_V          = 25,
    KB_W          = 26,
    KB_X          = 27,
    KB_Y          = 28,
    KB_Z          = 29,

    KB_0          = 30,
    KB_1          = 31,
    KB_2          = 32,
    KB_3          = 33,
    KB_4          = 34,
    KB_5          = 35,
    KB_6          = 36,
    KB_7          = 37,
    KB_8          = 38,
    KB_9          = 39,

    KB_RETURN     = 40,
    KB_ESCAPE     = 41,
    KB_BACKSPACE  = 42,
    KB_TAB        = 43,
    KB_SPACE      = 44,

    KB_MINUS      = 45,
    KB_EQUAL      = 46,
    KB_LBRACKET   = 47,
    KB_RBRACKET   = 48,
    KB_BACKSLASH  = 49,

    KB_RIGHT      = 79,
    KB_LEFT       = 80,
    KB_DOWN       = 81,
    KB_UP         = 82,
    
    KB_LCTRL      = 224,
    KB_LSHIFT     = 225,
    KB_LALT       = 226,
    KB_LMETA      = 227,

    KB_RCTRL      = 228,
    KB_RSHIFT     = 229,
    KB_RALT       = 230,
    KB_RMETA      = 231,

    KB_COUNT,
    KB_LAST       = KB_RSHIFT
};

// mouse button input
enum input_button
{
    MB_FIRST      = 0,

    MB_LEFT       = 0,
    MB_RIGHT      = 1,
    MB_MIDDLE     = 2,
    MB_FORWARD    = 3,
    MB_BACK       = 4,

    MB_COUNT,
    MB_LAST       = MB_COUNT - 1
};

enum input_state
{
    INPUT_DOWN         = 0x01,
    INPUT_UP           = 0x02,
    INPUT_PRESS        = 0x04,
    INPUT_REPEAT       = 0x08,

    INPUT_PREV_DOWN    = 0x10,
    INPUT_PREV_UP      = 0x20,
    INPUT_PREV_PRESS   = 0x40,
    INPUT_PREV_REPEAT  = 0x80
};

#ifdef __cplusplus
extern "C" {
#endif

int input_poll( void );

bool input_key_down( int key );
bool input_key_up( int key );
bool input_key_press( int key );

bool input_mouse_down( int button );
bool input_mouse_up( int button );
bool input_mouse_press( int button );
bool input_mouse_moved( void );
vec2_t input_mouse_pos( void );
vec2_t input_mouse_delta( void );
vec2_t input_mouse_scroll( void );

#ifdef __cplusplus
}
#endif

#endif
