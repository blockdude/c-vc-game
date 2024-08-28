#include "input.h"
#include "core.h"
#include <util/list.h>
#include <glad/glad.h>

static const int key_map[ SDL_NUM_SCANCODES ] = {
    KB_NONE,           // SDL_SCANCODE_UNKNOWN

    0, 0, 0,

    KB_A,              // SDL_SCANCODE_A
    KB_B,              // SDL_SCANCODE_B
    KB_C,              // SDL_SCANCODE_C
    KB_D,              // SDL_SCANCODE_D
    KB_E,              // SDL_SCANCODE_E
    KB_F,              // SDL_SCANCODE_F
    KB_G,              // SDL_SCANCODE_G
    KB_H,              // SDL_SCANCODE_H
    KB_I,              // SDL_SCANCODE_I
    KB_J,              // SDL_SCANCODE_J
    KB_K,              // SDL_SCANCODE_K
    KB_L,              // SDL_SCANCODE_L
    KB_M,              // SDL_SCANCODE_M
    KB_N,              // SDL_SCANCODE_N
    KB_O,              // SDL_SCANCODE_O
    KB_P,              // SDL_SCANCODE_P
    KB_Q,              // SDL_SCANCODE_Q
    KB_R,              // SDL_SCANCODE_R
    KB_S,              // SDL_SCANCODE_S
    KB_T,              // SDL_SCANCODE_T
    KB_U,              // SDL_SCANCODE_U
    KB_V,              // SDL_SCANCODE_V
    KB_W,              // SDL_SCANCODE_W
    KB_X,              // SDL_SCANCODE_X
    KB_Y,              // SDL_SCANCODE_Y
    KB_Z,              // SDL_SCANCODE_Z

    KB_1,              // SDL_SCANCODE_1
    KB_2,              // SDL_SCANCODE_2
    KB_3,              // SDL_SCANCODE_3
    KB_4,              // SDL_SCANCODE_4
    KB_5,              // SDL_SCANCODE_5
    KB_6,              // SDL_SCANCODE_6
    KB_7,              // SDL_SCANCODE_7
    KB_8,              // SDL_SCANCODE_8
    KB_9,              // SDL_SCANCODE_9
    KB_0,              // SDL_SCANCODE_0

    KB_RETURN,         // SDL_SCANCODE_RETURN
    KB_ESCAPE,         // SDL_SCANCODE_ESCAPE
    KB_BACKSPACE,      // SDL_SCANCODE_BACKSPACE
    KB_TAB,            // SDL_SCANCODE_TAB
    KB_SPACE,          // SDL_SCANCODE_SPACE
    KB_MINUS,          // SDL_SCANCODE_MINUS
    KB_EQUAL,          // SDL_SCANCODE_EQUALS
    KB_LBRACKET,       // SDL_SCANCODE_LEFTBRACKET
    KB_RBRACKET,       // SDL_SCANCODE_RIGHTBRACKET
    KB_BACKSLASH,      // SDL_SCANCODE_BACKSLASH
    0,                 // SDL_SCANCODE_NONUSHASH
    0,                 // SDL_SCANCODE_SEMICOLON
    0,                 // SDL_SCANCODE_APOSTROPHE
    0,                 // SDL_SCANCODE_GRAVE
    0,                 // SDL_SCANCODE_COMMA
    0,                 // SDL_SCANCODE_PERIOD
    0,                 // SDL_SCANCODE_SLASH
    0,                 // SDL_SCANCODE_CAPSLOCK
    0,                 // SDL_SCANCODE_F1
    0,                 // SDL_SCANCODE_F2
    0,                 // SDL_SCANCODE_F3
    0,                 // SDL_SCANCODE_F4
    0,                 // SDL_SCANCODE_F5
    0,                 // SDL_SCANCODE_F6
    0,                 // SDL_SCANCODE_F7
    0,                 // SDL_SCANCODE_F8
    0,                 // SDL_SCANCODE_F9
    0,                 // SDL_SCANCODE_F10
    0,                 // SDL_SCANCODE_F11
    0,                 // SDL_SCANCODE_F12
    0,                 // SDL_SCANCODE_PRINTSCREEN
    0,                 // SDL_SCANCODE_SCROLLLOCK
    0,                 // SDL_SCANCODE_PAUSE
    0,                 // SDL_SCANCODE_INSERT
    0,                 // SDL_SCANCODE_HOME
    0,                 // SDL_SCANCODE_PAGEUP
    0,                 // SDL_SCANCODE_DELETE
    0,                 // SDL_SCANCODE_END
    0,                 // SDL_SCANCODE_PAGEDOWN
    KB_RIGHT,          // SDL_SCANCODE_RIGHT
    KB_LEFT,           // SDL_SCANCODE_LEFT
    KB_DOWN,           // SDL_SCANCODE_DOWN
    KB_UP,             // SDL_SCANCODE_UP
    0,                 // SDL_SCANCODE_NUMLOCKCLEAR
    0,                 // SDL_SCANCODE_KP_DIVIDE
    0,                 // SDL_SCANCODE_KP_MULTIPLY
    0,                 // SDL_SCANCODE_KP_MINUS
    0,                 // SDL_SCANCODE_KP_PLUS
    0,                 // SDL_SCANCODE_KP_ENTER
    0,                 // SDL_SCANCODE_KP_1
    0,                 // SDL_SCANCODE_KP_2
    0,                 // SDL_SCANCODE_KP_3
    0,                 // SDL_SCANCODE_KP_4
    0,                 // SDL_SCANCODE_KP_5
    0,                 // SDL_SCANCODE_KP_6
    0,                 // SDL_SCANCODE_KP_7
    0,                 // SDL_SCANCODE_KP_8
    0,                 // SDL_SCANCODE_KP_9
    0,                 // SDL_SCANCODE_KP_0
    0,                 // SDL_SCANCODE_KP_PERIOD
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    KB_LCTRL,          //SDL_SCANCODE_LCTRL
    KB_LSHIFT,         //SDL_SCANCODE_LSHIFT
    KB_LALT,           //SDL_SCANCODE_LALT
    KB_LMETA,          //SDL_SCANCODE_LGUI
    KB_RCTRL,          //SDL_SCANCODE_RCTRL
    KB_RSHIFT,         //SDL_SCANCODE_RSHIFT
    KB_RALT,           //SDL_SCANCODE_RALT
    KB_RMETA,          //SDL_SCANCODE_RGUI
};

static const int button_map[] = {
    0,
    MB_LEFT,
    MB_MIDDLE,
    MB_RIGHT,
    MB_FORWARD,
    MB_BACK
};

static int get_key( SDL_Scancode code )
{
    return key_map[ code ];
}

static int get_button( int button )
{
    return button_map[ button ];
}

int input_poll( void )
{
    // reset keys
    for ( int i = 0; i < KB_COUNT; i++ )
        core.input.keyboard.state[ i ] &= ~( INPUT_DOWN | INPUT_UP );

    // reset mouse buttons
    for ( int i = 0; i < MB_COUNT; i++ )
        core.input.mouse.state[ i ] &= ~( INPUT_DOWN | INPUT_UP );

    // reset mouse events
    core.input.mouse.moved = false;
    core.input.mouse.wheel.x = 0;
    core.input.mouse.wheel.y = 0;
    core.input.mouse.pos.delta.x = 0;
    core.input.mouse.pos.delta.y = 0;

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

                core.window.w = event.window.data1;
                core.window.h = event.window.data2;
                core.window.aspect = ( float ) core.window.w / core.window.h;
                glViewport( 0, 0, core.window.w, core.window.h );

                break;

            case SDL_EVENT_KEY_DOWN:

                core.input.keyboard.state[ get_key( event.key.scancode ) ] = INPUT_DOWN | INPUT_PRESS;

                break;

            case SDL_EVENT_KEY_UP:

                core.input.keyboard.state[ get_key( event.key.scancode ) ] = INPUT_UP;

                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:

                core.input.mouse.state[ get_button( event.button.button ) ] = INPUT_DOWN | INPUT_PRESS;

                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:

                core.input.mouse.state[ get_button( event.button.button ) ] = INPUT_UP;

                break;

            case SDL_EVENT_MOUSE_WHEEL:

                core.input.mouse.wheel.x += event.wheel.x;
                core.input.mouse.wheel.y += event.wheel.y;

                break;

            case SDL_EVENT_MOUSE_MOTION:

                core.input.mouse.pos.rel.x = event.motion.x;
                core.input.mouse.pos.rel.y = event.motion.y;
                core.input.mouse.pos.delta.x += event.motion.xrel;
                core.input.mouse.pos.delta.y += event.motion.yrel;
                core.input.mouse.moved = true;

                break;
        }
    }

    return result;
}

bool input_key_down( int key )
{
    return core.input.keyboard.state[ key ] & INPUT_DOWN;
}

bool input_key_up( int key )
{
    return core.input.keyboard.state[ key ] & INPUT_UP;
}

bool input_key_press( int key )
{
    return core.input.keyboard.state[ key ] & INPUT_PRESS;
}

bool input_mouse_down( int button )
{
    return core.input.mouse.state[ button ] & INPUT_DOWN;
}

bool input_mouse_up( int button )
{
    return core.input.mouse.state[ button ] & INPUT_UP;
}

bool input_mouse_press( int button )
{
    return core.input.mouse.state[ button ] & INPUT_PRESS;
}

bool input_mouse_moved( void )
{
    return core.input.mouse.moved;
}

vec2_t input_mouse_pos( void )
{
    vec2_t result = { 0 };

    result.x = core.input.mouse.pos.rel.x;
    result.y = core.input.mouse.pos.rel.y;

    return result;
}

vec2_t input_mouse_delta( void )
{
    vec2_t result = { 0 };

    result.x = core.input.mouse.pos.delta.x;
    result.y = core.input.mouse.pos.delta.y;

    return result;
}

vec2_t input_mouse_scroll( void )
{
    vec2_t result = { 0 };

    result.x = core.input.mouse.wheel.x;
    result.y = core.input.mouse.wheel.y;

    return result;
}
