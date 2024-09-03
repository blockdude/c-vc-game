#ifndef STATE_H
#define STATE_H

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
