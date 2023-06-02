#ifndef STATE_H
#define STATE_H

#include "../gfx/window.h"
#include "../world/world.h"

#define DEFAULT_FRAME_RATE			60
#define DEFAULT_TICK_RATE			60

#define DEFAULT_WINDOW_WIDTH		700
#define DEFAULT_WINDOW_HEIGHT		700

extern struct world world;
extern struct window_state game_state;
extern struct window_state menu_state;
extern struct window_state collision_state;

#endif
