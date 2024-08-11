#ifndef STATE_H
#define STATE_H

#define DEFAULT_FRAME_RATE			60
#define DEFAULT_TICK_RATE			60

#define DEFAULT_WINDOW_WIDTH		700
#define DEFAULT_WINDOW_HEIGHT		700

// window function
typedef int ( *state_fn )( void );

struct state
{
	state_fn state;
};

struct state_machine
{
	struct state *current_state;
	void *context;
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
