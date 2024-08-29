#include "input.h"
#include "core.h"

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
