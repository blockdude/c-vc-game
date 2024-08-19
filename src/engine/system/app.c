#include "app.h"
#include <util/log.h>
#include <system/input.h>

static inline int internal_init( struct app *self )
{
    if ( self == NULL )
        return 1;

    if ( self->stage.init != NULL )
        self->stage.init( self );

    return 0;
}

static inline int internal_free( struct app *self )
{
    if ( self == NULL )
        return 1;

    if ( self->stage.free != NULL )
        self->stage.free( self );

    return 0;
}

static inline int internal_tick( struct app *self )
{
    if ( self == NULL )
        return 1;

    if ( self->stage.tick != NULL )
        self->stage.tick( self );

    self->tick_count++;

    return 0;
}

static inline int internal_update( struct app *self )
{
    if ( self == NULL )
        return 1;

    if ( self->stage.update != NULL )
        self->stage.update( self );

    return 0;
}

static inline int internal_render( struct app *self )
{
    if ( self == NULL )
        return 1;

    if ( self->stage.render != NULL )
        self->stage.render( self );

    self->frame_count++;

    return 0;
}

static int internal_loop( struct app *self )
{
    log_info( "Starting application loop" );
    internal_init( self );

    uint64_t frame_previous = SDL_GetTicks();
    double tick_time = 0;

    uint64_t tick_last = 0;
    uint64_t frame_last = 0;

    uint64_t frame_timer = frame_previous;

	// begin main loop
    while ( self->running )
    {
        // get frame timing
        uint64_t frame_current = SDL_GetTicks();
        uint64_t frame_delta = frame_current - frame_previous;

        // update fps & tps every second
        if ( frame_current - frame_timer >= TIMESCALE )
        {
            // get variables
            int ticks  = self->tick_count - tick_last;
            int frames = self->frame_count - frame_last;

            // store rate per second
            self->frame_rate = frames;
            self->tick_rate = ticks;

            // store this frame/tick
            tick_last  = self->tick_count;
            frame_last = self->frame_count;

            // reset timer
            frame_timer = frame_current;
        }

        frame_previous = frame_current;
        tick_time += frame_delta;

        // poll events
        if ( input_poll() == INPUT_QUIT )
            goto soft_exit;
        
        // maintain fixed time step for each tick
        while ( tick_time >= self->tick_target )
        {
            internal_tick( self );
            tick_time -= self->tick_target;
        }

        internal_update( self );
        internal_render( self );

        // calculate & store frame time
        self->frame_delta = frame_delta / TIMESCALE;

        // apply fps cap
        int delay = frame_current + self->frame_target - SDL_GetTicks();
        if ( delay > 0 ) SDL_Delay( delay );
    }

soft_exit:
	internal_free( self );
    return 0;
}

int app_init( struct app *self, struct stage state )
{
	self->stage        = state;
    self->running      = false;

	self->frame_delta  = 0;
	self->frame_target = TIMESCALE / 60.0f;
	self->frame_rate   = 0;
	self->frame_count  = 0;

	self->tick_delta   = 0;
	self->tick_target  = TIMESCALE / 30.0f;
	self->tick_rate    = 0;
	self->tick_count   = 0;

	return 0;
}

void app_loop( struct app *self )
{
    if ( self == NULL )
        return;

    self->running = true;
    internal_loop( self );
}

void app_stop( struct app *self )
{
    self->running = false;
}

void app_set_target_fps( struct app *self, float target )
{
    self->frame_target = target <= 0.0f ? 0.0f : TIMESCALE / target;
}

void app_set_target_tps( struct app *self, float target )
{
    self->tick_target = target <= 0.0f ? 0.0f : TIMESCALE / target;
}

int app_get_fps( struct app *self )
{
    return self->frame_rate;
}

int app_get_tps( struct app *self )
{
    return self->tick_rate;
}
