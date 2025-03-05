#ifndef VCP_INPUT_H
#define VCP_INPUT_H

#include "../common.h"
#include "../util/types.h"

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
    K_LAST       = K_RMETA
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
    bool pressed      : 1;
    bool released     : 1;
    bool down         : 1;
    bool repeated     : 1;
};

extern int input_init( void );
extern void input_deinit( void );
extern void input_poll_events( void );
extern int input_quit_event( void );
extern int input_text( char *buffer, size_t count );
extern struct keystate input_keystate( int key );
extern struct keystate input_btnstate( int btn );
extern bool input_mouse_moved( void );
extern struct vec2 input_mouse_pos( void );
extern struct vec2 input_mouse_delta( void );
extern struct vec2 input_mouse_scroll( void );

#endif
