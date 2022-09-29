#include "state.h"
#include "game.h"

struct window_state g_game_state = {
    .init   = game_init,
    .free   = game_free,
    .update = game_update,
    .tick   = game_tick,
    .render = game_render
};

struct window_state g_menu_state = {
    .init   = NULL,
    .free   = NULL,
    .update = NULL,
    .tick   = NULL,
    .render = NULL
};
