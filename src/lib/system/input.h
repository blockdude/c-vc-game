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
    K_FIRST      = 0,

    K_NONE       = 0,

    K_A          = 4,
    K_B          = 5,
    K_C          = 6,
    K_D          = 7,
    K_E          = 8,
    K_F          = 9,
    K_G          = 10,
    K_H          = 11,
    K_I          = 12,
    K_J          = 13,
    K_K          = 14,
    K_L          = 15,
    K_M          = 16,
    K_N          = 17,
    K_O          = 18,
    K_P          = 19,
    K_Q          = 20,
    K_R          = 21,
    K_S          = 22,
    K_T          = 23,
    K_U          = 24,
    K_V          = 25,
    K_W          = 26,
    K_X          = 27,
    K_Y          = 28,
    K_Z          = 29,

    K_0          = 30,
    K_1          = 31,
    K_2          = 32,
    K_3          = 33,
    K_4          = 34,
    K_5          = 35,
    K_6          = 36,
    K_7          = 37,
    K_8          = 38,
    K_9          = 39,

    K_RETURN     = 40,
    K_ESCAPE     = 41,
    K_BACKSPACE  = 42,
    K_TAB        = 43,
    K_SPACE      = 44,

    K_MINUS      = 45,
    K_EQUAL      = 46,
    K_LBRACKET   = 47,
    K_RBRACKET   = 48,
    K_BACKSLASH  = 49,

    K_RIGHT      = 79,
    K_LEFT       = 80,
    K_DOWN       = 81,
    K_UP         = 82,
    
    K_LCTRL      = 224,
    K_LSHIFT     = 225,
    K_LALT       = 226,
    K_LMETA      = 227,

    K_RCTRL      = 228,
    K_RSHIFT     = 229,
    K_RALT       = 230,
    K_RMETA      = 231,

    K_COUNT,
    K_LAST       = K_RSHIFT
};

// mouse button input
enum input_button
{
    B_FIRST      = 0,

    B_LEFT       = 0,
    B_RIGHT      = 1,
    B_MIDDLE     = 2,
    B_FORWARD    = 3,
    B_BACK       = 4,

    B_COUNT,
    B_LAST       = B_COUNT - 1
};

enum input_state
{
    S_DOWN       = 0x01,
    S_UP         = 0x02,
    S_PRESS      = 0x04,
    S_REPEAT     = 0x08,

    P_DOWN       = 0x10,
    P_UP         = 0x20,
    P_PRESS      = 0x40,
    P_REPEAT     = 0x80
};

#ifdef __cplusplus
extern "C" {
#endif

// poll all events
int    input_poll( void );

/*
 * Check input state of a key.
 * Returns true if any state is true.
 */
bool   input_key( int key, unsigned int sflags );

/*
 * Returns true if key is held down.
 */
bool   input_key_press( int key );

/*
 * Returns true if key is pressed.
 * Lasts one frame.
 */
bool   input_key_down( int key );

/*
 * Returns true if key is released.
 * Lasts one frame.
 */
bool   input_key_up( int key );

/*
 * Check input state of a key.
 * Returns true if any state is true.
 */
bool   input_button( int key, unsigned int sflags );

/*
 * Returns true if key is held down.
 */
bool   input_button_press( int button );

/*
 * Returns true if key is pressed.
 * Lasts one frame.
 */
bool   input_button_down( int button );

/*
 * Returns true if key is released.
 * Lasts one frame.
 */
bool   input_button_up( int button );

bool   input_mouse_moved( void );
vec2_t input_mouse_pos( void );
vec2_t input_mouse_delta( void );
vec2_t input_mouse_scroll( void );

#ifdef __cplusplus
}
#endif

#endif
