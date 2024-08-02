#include "state.h"

struct state state = {
    .game = {
        .init   = NULL,
        .free   = NULL,
        .tick   = NULL,
        .update = NULL,
        .render = NULL
    },
    .menu = {
        .init   = NULL,
        .free   = NULL,
        .tick   = NULL,
        .update = NULL,
        .render = NULL
    }
};
