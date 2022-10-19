#include "state.h"
#include "game.h"

struct world world;

struct window_state game_state = {
    .init   = game_init,
    .free   = game_free,
    .tick   = game_tick,
    .update = game_update,
    .render = game_render
};

struct window_state menu_state = {
    .init   = NULL,
    .free   = NULL,
    .tick   = NULL,
    .update = NULL,
    .render = NULL
};
