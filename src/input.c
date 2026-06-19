#include <vcp/vcp.h>
#include <assert.h>
#include <SDL3/SDL.h>
#include "window.h"

#define INPUT_HISTORY_LEN 64

static const enum InputKey key_map[SDL_SCANCODE_COUNT] = {
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

static const enum InputButton button_map[] = {
    0,
    B_LEFT,           // SDL_BUTTON_LEFT
    B_MIDDLE,         // SDL_BUTTON_MIDDLE
    B_RIGHT,          // SDL_BUTTON_RIGHT
    B_FORWARD,        // SDL_BUTTON_X1
    B_BACK            // SDL_BUTTON_X2
};

static struct
{
    bool         	    initialized;
    struct InputState   k_state[K_COUNT];
    struct InputState   m_state[B_COUNT];
    bool         	    m_moved;
    struct Vec2         m_wheel;
    struct Vec2         m_pos_rel;
    struct Vec2         m_pos_global;
    struct Vec2         m_pos_delta;
    bool                e_quit;

    int                 k_history_count;
    int                 m_history_count;
    enum InputKey       k_history[INPUT_HISTORY_LEN];
    enum InputButton    m_history[INPUT_HISTORY_LEN];

    int                 text_buffer_count;
    char                text_buffer[VCP_MAX_STRING_LEN];
} state = { 0 };



/*
 * =============================
 * -----------------------------
 * INIT
 * -----------------------------
 */

int input_init(void)
{
    if (SDL_InitSubSystem(SDL_INIT_EVENTS) == false)
    {
        log_warn("Unable to initialize SDL event system: %s", SDL_GetError());
        return -1;
    }

    memset(&state, 0, sizeof(state));
    state.initialized = true;
    return 0;
}

void input_deinit(void)
{
    if (state.initialized == false)
        return;

    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    state.initialized = false;
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

void input_poll_events(bool capture_text)
{
    SDL_Window *window = (SDL_Window *)window_handle();
    bool is_capture_text_active = SDL_TextInputActive(window);

    // handle text input
    if (capture_text && !is_capture_text_active)
    {
        SDL_StartTextInput(window);
    }
    else if (!capture_text && is_capture_text_active)
    {
        SDL_StopTextInput(window);
    }

    // reset keys
    for (int i = 0; i < K_COUNT; i++)
    {
        state.k_state[i].pressed = false;
        state.k_state[i].released = false;
    }

    // reset mouse buttons
    for (int i = 0; i < B_COUNT; i++)
    {
        state.m_state[i].pressed = false;
        state.m_state[i].released = false;
    }

    // reset history count
    state.k_history_count = 0;
    state.m_history_count = 0;

    // reset text input
    memset(state.text_buffer, 0, VCP_MAX_STRING_LEN);
    state.text_buffer_count = 0;

    // reset mouse events
    state.m_moved = false;
    state.m_wheel.x = 0;
    state.m_wheel.y = 0;
    state.m_pos_delta.x = 0;
    state.m_pos_delta.y = 0;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // note: SDL_EVENT_QUIT does not provide a windowID
        if (event.type == SDL_EVENT_QUIT)
        {
            window_request_close();
            state.e_quit = true;
            return;
        }

        if (window_id() != event.window.windowID)
            continue;

        switch (event.type)
        {
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:

            window_request_close();

            break;

        case SDL_EVENT_WINDOW_RESIZED:

            window_update_viewport(event.window.data1, event.window.data2);

            break;

        case SDL_EVENT_KEY_DOWN:

            state.k_state[key_map[event.key.scancode]].pressed = true;
            state.k_state[key_map[event.key.scancode]].down = true;
            state.k_history[state.k_history_count] = key_map[event.key.scancode];
            state.k_history_count += (state.k_history_count < INPUT_HISTORY_LEN);

            break;

        case SDL_EVENT_KEY_UP:

            state.k_state[key_map[event.key.scancode]].down = false;
            state.k_state[key_map[event.key.scancode]].released = true;

            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:

            state.m_state[button_map[event.button.button]].pressed = true;
            state.m_state[button_map[event.button.button]].down = true;
            state.m_history[state.m_history_count] = button_map[event.button.button];
            state.m_history_count += (state.m_history_count < INPUT_HISTORY_LEN);

            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:

            state.m_state[button_map[event.button.button]].down = false;
            state.m_state[button_map[event.button.button]].released = true;

            break;

        case SDL_EVENT_MOUSE_WHEEL:

            state.m_wheel.x += event.wheel.x;
            state.m_wheel.y += event.wheel.y;

            break;

        case SDL_EVENT_MOUSE_MOTION:

            state.m_pos_rel.x = event.motion.x;
            state.m_pos_rel.y = event.motion.y;
            state.m_pos_delta.x += event.motion.xrel;
            state.m_pos_delta.y += event.motion.yrel;
            state.m_moved = true;

            break;

        case SDL_EVENT_TEXT_INPUT:

            state.text_buffer_count += snprintf(&state.text_buffer[state.text_buffer_count], VCP_MAX_STRING_LEN - state.text_buffer_count, "%s", event.text.text);
            state.text_buffer_count = MIN(state.text_buffer_count, VCP_MAX_STRING_LEN - 1);

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

bool input_quit_event(void)
{
    return state.e_quit;
}

int input_text_history_size(void)
{
    return state.text_buffer_count;
}

char input_text_history(int i)
{
    if (i < 0 || i >= state.text_buffer_count)
        return '\0';

    return state.text_buffer[i];
}

int input_text_history_buffer(char *buffer, size_t buffer_size)
{
    /*
    * Returns: the number of characters copied to
    * the buffer excluding the null character. So
    * it should only ever return buffer_size - 1
    * at most. The output buffer should always be
    * null terminated. If the buffer is NULL then
    * return the minimum size the buffer can be
    * to fully contain the text minus the null
    * character.
    */

    if ((buffer == NULL) || (buffer_size <= 0))
        return state.text_buffer_count;

    const int result = snprintf(buffer, buffer_size, "%.*s", state.text_buffer_count, state.text_buffer);
    return MIN(result, (int)buffer_size - 1);
}

int input_key_history_size(void)
{
    return state.k_history_count;
}

int input_button_history_size(void)
{
    return state.m_history_count;
}

enum InputKey input_key_history(int i)
{
    if (i < 0 || i >= state.k_history_count)
        return K_NONE;

    return state.k_history[i];
}

enum InputButton input_button_history(int i)
{
    if (i < 0 || i >= state.m_history_count)
        return B_NONE;

    return state.m_history[i];
}

int input_key_history_buffer(enum InputKey *buffer, size_t buffer_size)
{
    if (buffer == NULL || buffer_size == 0)
        return state.k_history_count;

    const int count = MIN(state.k_history_count, buffer_size);
    memcpy(buffer, state.k_history, sizeof(*buffer) * count);
    return count;
}

int input_button_history_buffer(enum InputButton *buffer, size_t buffer_size)
{
    if (buffer == NULL || buffer_size == 0)
        return state.m_history_count;

    const int count = MIN(state.m_history_count, buffer_size);
    memcpy(buffer, state.m_history, sizeof(*buffer) * count);
    return count;
}

struct InputState input_key_state(enum InputKey key)
{
    size_t index = (size_t)key;
    assert((index >= 0) && (index < K_COUNT));
    return state.k_state[index];
}

struct InputState input_button_state(enum InputButton button)
{
    size_t index = (size_t)button;
    assert((index >= 0) && (index < B_COUNT));
    return state.m_state[index];
}

void input_warp_mouse(float x, float y)
{
    SDL_WarpMouseInWindow(window_handle(), x, y);
}

void input_warp_mouse_global(float x, float y)
{
    SDL_WarpMouseGlobal(x, y);
}

bool input_mouse_moved(void)
{
    return state.m_moved;
}

struct Vec2 input_mouse_position(void)
{
    struct Vec2 res;
    SDL_GetMouseState(&res.x, &res.y);
    return res;
}

struct Vec2 input_mouse_global_position(void)
{
    struct Vec2 res;
    SDL_GetGlobalMouseState(&res.x, &res.y);
    return res;
}

struct Vec2 input_mouse_motion_position(void)
{
    return state.m_pos_rel;
}

struct Vec2 input_mouse_delta(void)
{
    return state.m_pos_delta;
}

struct Vec2 input_mouse_scroll(void)
{
    return state.m_wheel;
}

/*
 * =============================
 */
