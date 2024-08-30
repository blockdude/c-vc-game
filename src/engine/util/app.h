#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdint.h>
#include <stdbool.h>

struct app;
typedef int ( *event_fn )( struct app *app );

struct app
{
	event_fn init;
	event_fn free;
	event_fn tick;
	event_fn update;
	event_fn render;

	bool running;
	bool skip_ticks;

	float    frame_delta;
	float    frame_target;
	float    frame_avg;
	int      frame_rate;
	uint64_t frame_count;

	float    tick_delta;
	float    tick_target;
	float    tick_avg;
	int      tick_rate;
	uint64_t tick_count;
};

#ifdef __cplusplus
extern "C" {
#endif

int  app_init( struct app *self, event_fn init, event_fn free, event_fn tick, event_fn update, event_fn render );
void app_loop( struct app *self );
void app_stop( struct app *self );

void app_target_fps_set( struct app *self, float target );
void app_target_tps_set( struct app *self, float target );
int  app_fps( struct app *self );
int  app_tps( struct app *self );

#ifdef __cplusplus
}
#endif

#endif
