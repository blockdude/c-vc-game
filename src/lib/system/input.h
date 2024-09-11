#ifndef INPUT_H
#define INPUT_H

#include <util/types.h>

enum input_status
{
    INPUT_ERROR   = -1,
    INPUT_SUCCESS =  0,
    INPUT_QUIT    =  1
};

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

enum input_btn
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

struct keystate
{
    // Key was pressed this frame
    bool just_pressed : 1;
    // Key was released this frame
    bool released     : 1;
    // Key is being pressed down
    bool pressed      : 1;
    // Key was double pressed within a certain time period
    bool repeated     : 1;
};

#ifdef __cplusplus
extern "C" {
#endif

// poll all events
int input_poll( void );

/*
 * Returns the keystate of given key
 */
struct keystate input_keystate( int key );

/*
 * Returns the keystate of given button
 */
struct keystate input_btnstate( int btn );

/*
 * Returns true if the mouse was moved.
 * Lasts one frame.
 */
bool input_mouse_moved( void );

/*
 * Returns a 2d vector of the current mouse position relative to
 * the screen.
 */
vec2_t input_mouse_pos( void );

/*
 * Returns the amount the mouse has moved between the current
 * frame and the previous frame.
 */
vec2_t input_mouse_delta( void );

/*
 * Returns the amount the mouse wheel has been scrolled between
 * the current frame and the previous frame.
 */
vec2_t input_mouse_scroll( void );

#ifdef __cplusplus
}
#endif

#endif
