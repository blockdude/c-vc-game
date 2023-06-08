#include "state.h"
#include "game.h"

struct state state = {
    .game = {
        .init   = game_init,
        .free   = game_free,
        .tick   = game_tick,
        .update = game_update,
        .render = game_render
    },
    .menu = {
        .init   = NULL,
        .free   = NULL,
        .tick   = NULL,
        .update = NULL,
        .render = NULL
    }
};
