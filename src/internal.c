#include "internal.h"

struct core core = {
    .window.initialized = false,
    .window.flags = 0,
    .window.title = "Application",
    .window.width = 700,
    .window.height = 700,
    .window.aspect = 1.0f,

    .input = { 0 },
    .timer = { 0 },
    .audio = { 0 }
};