#ifndef EVENT_H
#define EVENT_H

#include <stdint.h>
#include <stdbool.h>

struct game;
typedef int ( *event_fn )( struct game* );

// stage of events
struct stage
{
	// our event pipeline
	event_fn init;
	event_fn free;
	event_fn tick;
	event_fn update;
	event_fn render;
};

struct game
{
	struct stage stage;
	bool running;

	// frame timing
	double   frame_delta;
	double   frame_target;
	uint64_t frame_rate;
	uint64_t frame_count;

	// tick timing
	double   tick_delta;
	double   tick_target;
	uint64_t tick_rate;
	uint64_t tick_count;
};

#ifdef __cplusplus
extern "C" {
#endif

int  game_init( struct game *gm, struct stage state );
void game_loop( struct game *gm );
void game_stop( struct game *gm );

void game_set_target_fps( struct game *gm, double target );
void game_set_target_tps( struct game *gm, double target );
uint64_t game_get_fps( struct game *gm );
uint64_t game_get_tps( struct game *gm );

#ifdef __cplusplus
}
#endif

#endif
