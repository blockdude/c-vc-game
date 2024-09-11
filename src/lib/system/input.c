#include "input.h"
#include "global.h"

#include <SDL3/SDL.h>
#include <glad/gl.h>

static const int keymap[ SDL_NUM_SCANCODES ] = {
    K_NONE,           // SDL_SCANCODE_UNKNOWN

    0, 0, 0,

    K_A,              // SDL_SCANCODE_A
    K_B,              // SDL_SCANCODE_B
    K_C,              // SDL_SCANCODE_C
    K_D,              // SDL_SCANCODE_D
    K_E,              // SDL_SCANCODE_E
    K_F,              // SDL_SCANCODE_F
    K_G,              // SDL_SCANCODE_G
    K_H,              // SDL_SCANCODE_H
    K_I,              // SDL_SCANCODE_I
    K_J,              // SDL_SCANCODE_J
    K_K,              // SDL_SCANCODE_K
    K_L,              // SDL_SCANCODE_L
    K_M,              // SDL_SCANCODE_M
    K_N,              // SDL_SCANCODE_N
    K_O,              // SDL_SCANCODE_O
    K_P,              // SDL_SCANCODE_P
    K_Q,              // SDL_SCANCODE_Q
    K_R,              // SDL_SCANCODE_R
    K_S,              // SDL_SCANCODE_S
    K_T,              // SDL_SCANCODE_T
    K_U,              // SDL_SCANCODE_U
    K_V,              // SDL_SCANCODE_V
    K_W,              // SDL_SCANCODE_W
    K_X,              // SDL_SCANCODE_X
    K_Y,              // SDL_SCANCODE_Y
    K_Z,              // SDL_SCANCODE_Z

    K_1,              // SDL_SCANCODE_1
    K_2,              // SDL_SCANCODE_2
    K_3,              // SDL_SCANCODE_3
    K_4,              // SDL_SCANCODE_4
    K_5,              // SDL_SCANCODE_5
    K_6,              // SDL_SCANCODE_6
    K_7,              // SDL_SCANCODE_7
    K_8,              // SDL_SCANCODE_8
    K_9,              // SDL_SCANCODE_9
    K_0,              // SDL_SCANCODE_0

    K_RETURN,         // SDL_SCANCODE_RETURN
    K_ESCAPE,         // SDL_SCANCODE_ESCAPE
    K_BACKSPACE,      // SDL_SCANCODE_BACKSPACE
    K_TAB,            // SDL_SCANCODE_TAB
    K_SPACE,          // SDL_SCANCODE_SPACE
    K_MINUS,          // SDL_SCANCODE_MINUS
    K_EQUAL,          // SDL_SCANCODE_EQUALS
    K_LBRACKET,       // SDL_SCANCODE_LEFTBRACKET
    K_RBRACKET,       // SDL_SCANCODE_RIGHTBRACKET
    K_BACKSLASH,      // SDL_SCANCODE_BACKSLASH

    0,                // SDL_SCANCODE_NONUSHASH
    0,                // SDL_SCANCODE_SEMICOLON
    0,                // SDL_SCANCODE_APOSTROPHE
    0,                // SDL_SCANCODE_GRAVE
    0,                // SDL_SCANCODE_COMMA
    0,                // SDL_SCANCODE_PERIOD
    0,                // SDL_SCANCODE_SLASH
    0,                // SDL_SCANCODE_CAPSLOCK
    0,                // SDL_SCANCODE_F1
    0,                // SDL_SCANCODE_F2
    0,                // SDL_SCANCODE_F3
    0,                // SDL_SCANCODE_F4
    0,                // SDL_SCANCODE_F5
    0,                // SDL_SCANCODE_F6
    0,                // SDL_SCANCODE_F7
    0,                // SDL_SCANCODE_F8
    0,                // SDL_SCANCODE_F9
    0,                // SDL_SCANCODE_F10
    0,                // SDL_SCANCODE_F11
    0,                // SDL_SCANCODE_F12
    0,                // SDL_SCANCODE_PRINTSCREEN
    0,                // SDL_SCANCODE_SCROLLLOCK
    0,                // SDL_SCANCODE_PAUSE
    0,                // SDL_SCANCODE_INSERT
    0,                // SDL_SCANCODE_HOME
    0,                // SDL_SCANCODE_PAGEUP
    0,                // SDL_SCANCODE_DELETE
    0,                // SDL_SCANCODE_END
    0,                // SDL_SCANCODE_PAGEDOWN

    K_RIGHT,          // SDL_SCANCODE_RIGHT
    K_LEFT,           // SDL_SCANCODE_LEFT
    K_DOWN,           // SDL_SCANCODE_DOWN
    K_UP,             // SDL_SCANCODE_UP

    0,                // SDL_SCANCODE_NUMLOCKCLEAR
    0,                // SDL_SCANCODE_KP_DIVIDE
    0,                // SDL_SCANCODE_KP_MULTIPLY
    0,                // SDL_SCANCODE_KP_MINUS
    0,                // SDL_SCANCODE_KP_PLUS
    0,                // SDL_SCANCODE_KP_ENTER
    0,                // SDL_SCANCODE_KP_1
    0,                // SDL_SCANCODE_KP_2
    0,                // SDL_SCANCODE_KP_3
    0,                // SDL_SCANCODE_KP_4
    0,                // SDL_SCANCODE_KP_5
    0,                // SDL_SCANCODE_KP_6
    0,                // SDL_SCANCODE_KP_7
    0,                // SDL_SCANCODE_KP_8
    0,                // SDL_SCANCODE_KP_9
    0,                // SDL_SCANCODE_KP_0
    0,                // SDL_SCANCODE_KP_PERIOD

    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    K_LCTRL,          // SDL_SCANCODE_LCTRL
    K_LSHIFT,         // SDL_SCANCODE_LSHIFT
    K_LALT,           // SDL_SCANCODE_LALT
    K_LMETA,          // SDL_SCANCODE_LGUI
    K_RCTRL,          // SDL_SCANCODE_RCTRL
    K_RSHIFT,         // SDL_SCANCODE_RSHIFT
    K_RALT,           // SDL_SCANCODE_RALT
    K_RMETA,          // SDL_SCANCODE_RGUI
};

static const int btnmap[] = {
    0,
    B_LEFT,           // SDL_BUTTON_LEFT
    B_MIDDLE,         // SDL_BUTTON_MIDDLE
    B_RIGHT,          // SDL_BUTTON_RIGHT
    B_FORWARD,        // SDL_BUTTON_X1
    B_BACK            // SDL_BUTTON_X2
};

int input_poll( void )
{
    // reset keys
    for ( int i = 0; i < K_COUNT; i++ )
        core.input.k_state[ i ] &= ~( S_DOWN | S_UP );

    // reset mouse buttons
    for ( int i = 0; i < B_COUNT; i++ )
        core.input.m_state[ i ] &= ~( S_DOWN | S_UP );

    // reset mouse events
    core.input.m_moved       = false;
    core.input.m_wheel.x     = 0;
    core.input.m_wheel.y     = 0;
    core.input.m_pos_delta.x = 0;
    core.input.m_pos_delta.y = 0;

    int result = INPUT_SUCCESS;

    SDL_Event event;
    while ( SDL_PollEvent( &event ) )
    {
        switch ( event.type )
        {
            case SDL_EVENT_QUIT:

                result = INPUT_QUIT;

                break;

            case SDL_EVENT_WINDOW_RESIZED:

                core.window.width  = event.window.data1;
                core.window.height = event.window.data2;
                core.window.aspect = ( float ) core.window.width / core.window.height;
                glViewport( 0, 0, core.window.width, core.window.height );

                break;

            case SDL_EVENT_KEY_DOWN:

                core.input.k_state[ keymap[ event.key.scancode ] ] = S_DOWN | S_PRESS;

                break;

            case SDL_EVENT_KEY_UP:

                core.input.k_state[ keymap[ event.key.scancode ] ] = S_UP;

                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:

                core.input.m_state[ btnmap[ event.button.button ] ] = S_DOWN | S_PRESS;

                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:

                core.input.m_state[ btnmap[ event.button.button ] ] = S_UP;

                break;

            case SDL_EVENT_MOUSE_WHEEL:

                core.input.m_wheel.x += event.wheel.x;
                core.input.m_wheel.y += event.wheel.y;

                break;

            case SDL_EVENT_MOUSE_MOTION:

                core.input.m_pos_rel.x    = event.motion.x;
                core.input.m_pos_rel.y    = event.motion.y;
                core.input.m_pos_delta.x += event.motion.xrel;
                core.input.m_pos_delta.y += event.motion.yrel;
                core.input.m_moved = true;

                break;
        }
    }

    return result;
}

bool input_key( int key, unsigned int sflags )
{
    return ( core.input.k_state[ key ] & sflags ) > 0;
}

bool input_btn( int key, unsigned int sflags )
{
    return ( core.input.m_state[ key ] & sflags ) > 0;
}

bool input_key_down( int key )
{
    return core.input.k_state[ key ] & S_DOWN;
}

bool input_key_up( int key )
{
    return core.input.k_state[ key ] & S_UP;
}

bool input_key_press( int key )
{
    return core.input.k_state[ key ] & S_PRESS;
}

bool input_btn_down( int button )
{
    return core.input.m_state[ button ] & S_DOWN;
}

bool input_btn_up( int button )
{
    return core.input.m_state[ button ] & S_UP;
}

bool input_btn_press( int button )
{
    return core.input.m_state[ button ] & S_PRESS;
}

bool input_mouse_moved( void )
{
    return core.input.m_moved;
}

vec2_t input_mouse_pos( void )
{
    return core.input.m_pos_rel;
}

vec2_t input_mouse_delta( void )
{
    return core.input.m_pos_delta;
}

vec2_t input_mouse_scroll( void )
{
    return core.input.m_wheel;
}
