#include "input.h"
#include "window.h"
#include "../util/log.h"

#include <SDL3/SDL.h>
#include <glad/gl.h>

static const int keymap[ SDL_SCANCODE_COUNT ] = {
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

static struct
{
    bool         	initialized;
    struct keystate k_state[ K_COUNT ];
    struct keystate m_state[ B_COUNT ];
    bool         	m_moved;
    struct vec2     m_wheel;
    struct vec2     m_pos_rel;
    struct vec2     m_pos_global;
    struct vec2     m_pos_delta;
} g_input_state = { 0 };

/*
 * =============================
 * -----------------------------
 * INIT
 * -----------------------------
 */

int input_init( void )
{
    if ( SDL_InitSubSystem( SDL_INIT_EVENTS ) == false )
    {
        log_warn( "Unable to initialize SDL event system: %s", SDL_GetError() );
        return -1;
    }

    memset( &g_input_state, 0, sizeof( g_input_state ) );
    g_input_state.initialized = true;
    return 0;
}

void input_deinit( void )
{
    if ( g_input_state.initialized == false )
        return;

    SDL_QuitSubSystem( SDL_INIT_EVENTS );
    g_input_state.initialized = false;
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * POLL EVENTS
 * -----------------------------
 */

void input_poll_events( void )
{
    // reset keys
    for ( int i = 0; i < K_COUNT; i++ )
    {
        g_input_state.k_state[ i ].just_pressed = false;
        g_input_state.k_state[ i ].released = false;
    }

    // reset mouse buttons
    for ( int i = 0; i < B_COUNT; i++ )
    {
        g_input_state.m_state[ i ].just_pressed = false;
        g_input_state.m_state[ i ].released = false;
    }

    // reset mouse events
    g_input_state.m_moved       = false;
    g_input_state.m_wheel.x     = 0;
    g_input_state.m_wheel.y     = 0;
    g_input_state.m_pos_delta.x = 0;
    g_input_state.m_pos_delta.y = 0;

    SDL_Event event;
    while ( SDL_PollEvent( &event ) )
    {
        // note: SDL_EVENT_QUIT does not provide a windowID
        if ( event.type == SDL_EVENT_QUIT )
        {
            _window_notify( _WINDOW_NOTIFY_CLOSE, 0, 0 );
            return;
        }

        if ( window_id() != event.window.windowID )
            continue;

        switch ( event.type )
        {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:

                _window_notify( _WINDOW_NOTIFY_CLOSE, 0, 0 );

                break;

            case SDL_EVENT_WINDOW_RESIZED:

                _window_notify( _WINDOW_NOTIFY_RESIZE, event.window.data1, event.window.data2 );

                break;

            case SDL_EVENT_KEY_DOWN:

                g_input_state.k_state[ keymap[ event.key.scancode ] ].just_pressed = true;
                g_input_state.k_state[ keymap[ event.key.scancode ] ].pressed = true;

                break;

            case SDL_EVENT_KEY_UP:

                g_input_state.k_state[ keymap[ event.key.scancode ] ].pressed = false;
                g_input_state.k_state[ keymap[ event.key.scancode ] ].released = true;

                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:

                g_input_state.m_state[ btnmap[ event.button.button ] ].just_pressed = true;
                g_input_state.m_state[ btnmap[ event.button.button ] ].pressed = true;

                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:

                g_input_state.m_state[ btnmap[ event.button.button ] ].pressed = false;
                g_input_state.m_state[ btnmap[ event.button.button ] ].released = true;

                break;

            case SDL_EVENT_MOUSE_WHEEL:

                g_input_state.m_wheel.x += event.wheel.x;
                g_input_state.m_wheel.y += event.wheel.y;

                break;

            case SDL_EVENT_MOUSE_MOTION:

                g_input_state.m_pos_rel.x    = event.motion.x;
                g_input_state.m_pos_rel.y    = event.motion.y;
                g_input_state.m_pos_delta.x += event.motion.xrel;
                g_input_state.m_pos_delta.y += event.motion.yrel;
                g_input_state.m_moved = true;

                break;
        }
    }
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * GET STATES
 * -----------------------------
 */

struct keystate input_keystate( int key )
{
    return g_input_state.k_state[ key ];
}

struct keystate input_btnstate( int btn )
{
    return g_input_state.m_state[ btn ];
}

bool input_mouse_moved( void )
{
    return g_input_state.m_moved;
}

struct vec2 input_mouse_pos( void )
{
    return g_input_state.m_pos_rel;
}

struct vec2 input_mouse_delta( void )
{
    return g_input_state.m_pos_delta;
}

struct vec2 input_mouse_scroll( void )
{
    return g_input_state.m_wheel;
}

/*
 * =============================
 */
