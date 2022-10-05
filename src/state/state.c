#include "state.h"
#include "game.h"

struct world world;

struct window_state game_state = {
    .init   = ( window_event_fn ) game_init,
    .free   = ( window_event_fn ) game_free,
    .tick   = ( window_event_fn ) game_tick,
    .update = ( window_event_fn ) game_update,
    .render = ( window_event_fn ) game_render
};

struct window_state menu_state = {
    .init   = NULL,
    .free   = NULL,
    .tick   = NULL,
    .update = NULL,
    .render = NULL
};
