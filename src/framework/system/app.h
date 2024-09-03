#ifndef APPLICATION_H
#define APPLICATION_H

#include <util/types.h>

struct app;
typedef int ( *event_fn )( void );

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

int  app_init( event_fn init, event_fn free, event_fn tick, event_fn update, event_fn render );
void app_loop( void );
void app_stop( void );

struct app *app_handle( void );
void app_target_fps_set( float target );
void app_target_tps_set( float target );
int  app_fps( void );
int  app_tps( void );

#ifdef __cplusplus
}
#endif

#endif
