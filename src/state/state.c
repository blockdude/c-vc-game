#include "state.h"
#include "game.h"
#include "collision-state.h"

struct world world;

struct window_state collision_state = {
    .init   = collision_state_init,
    .free   = collision_state_free,
    .tick   = collision_state_tick,
    .update = collision_state_update,
    .render = collision_state_render
};

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
