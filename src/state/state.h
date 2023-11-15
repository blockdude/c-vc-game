#ifndef STATE_H
#define STATE_H

#include "../gfx/window.h"
#include "../world/world.h"

#define DEFAULT_FRAME_RATE			60
#define DEFAULT_TICK_RATE			60

#define DEFAULT_WINDOW_WIDTH		700
#define DEFAULT_WINDOW_HEIGHT		700

struct state {
	struct world world;
	struct window_state game;
	struct window_state menu;
};

extern struct state state;

/*
 * This is if I want to move some of the window functions to
 * here instead.
 */

/*
typedef int ( *state_fn )( void );

enum state_phase
{
	STATE_PHASE_FIRST = 0,

	STATE_PHASE_INIT = 0,
	STATE_PHASE_FREE,
	STATE_PHASE_TICK,
	STATE_PHASE_UPDATE,
	STATE_PHASE_RENDER,

	STATE_PHASE_COUNT,
	STATE_PHASE_LAST = STATE_PHASE_COUNT - 1
	
};

struct timing1
{
	int target_rate;
	double target_delta;
	int rate;
	double delta;
	uint64_t count;
};

struct state_pipeline
{
	union {
		state_fn list[ STATE_PHASE_COUNT ];

		struct {
			state_fn init;
			state_fn free;
			state_fn tick;
			state_fn update;
			state_fn render;
		};
	} phase;
};

struct state {
    struct window window;
    struct render render;

	struct state_pipeline pipeline

	struct timing1 frame;
	struct timing1 tick;
};
*/

#endif
