#include "input.h"
#include "internal/core.h"
#include "internal/sys.h"

int input_poll( void )
{
    return sys_poll_events();
}

bool input_key_down( int key )
{
    return core.input.keyboard.state[ key ] & KEY_STATE_DOWN;
}

bool input_key_up( int key )
{
    return core.input.keyboard.state[ key ] & KEY_STATE_UP;
}

bool input_key_press( int key )
{
    return core.input.keyboard.state[ key ] & KEY_STATE_PRESS;
}

bool input_mouse_down( int button )
{
    return core.input.mouse.state[ button ] & KEY_STATE_DOWN;
}

bool input_mouse_up( int button )
{
    return core.input.mouse.state[ button ] & KEY_STATE_UP;
}

bool input_mouse_press( int button )
{
    return core.input.mouse.state[ button ] & KEY_STATE_PRESS;
}

bool input_mouse_moved( void )
{
    return core.input.mouse.moved;
}

vec2_t input_mouse_pos( void )
{
    return core.input.mouse.pos.rel;
}

vec2_t input_mouse_delta( void )
{
    return core.input.mouse.pos.delta;
}

vec2_t input_mouse_scroll( void )
{
    return core.input.mouse.wheel;
}
