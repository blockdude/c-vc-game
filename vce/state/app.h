#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdint.h>
#include <stdbool.h>

struct app;
typedef int ( *event_fn )( struct app* );

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

struct app
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

int  app_init( struct app *self, struct stage state );
void app_loop( struct app *self );
void app_stop( struct app *self );

void app_set_target_fps( struct app *self, double target );
void app_set_target_tps( struct app *self, double target );
uint64_t app_get_fps( struct app *self );
uint64_t app_get_tps( struct app *self );

#ifdef __cplusplus
}
#endif

#endif
