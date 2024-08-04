#include "stage.h"
#include <util/log.h>
#include <system/input.h>

static inline int internal_init_( struct game *gm )
{
    if ( gm == NULL )
        return 1;

    if ( gm->stage.init != NULL )
        gm->stage.init( gm );

    return 0;
}

static inline int internal_free_( struct game *gm )
{
    if ( gm == NULL )
        return 1;

    if ( gm->stage.free != NULL )
        gm->stage.free( gm );

    return 0;
}

static inline int internal_tick_( struct game *gm )
{
    if ( gm == NULL )
        return 1;

    if ( gm->stage.tick != NULL )
        gm->stage.tick( gm );

    gm->tick_count++;

    return 0;
}

static inline int internal_update_( struct game *gm )
{
    if ( gm == NULL )
        return 1;

    if ( gm->stage.update != NULL )
        gm->stage.update( gm );

    return 0;
}

static inline int internal_render_( struct game *gm )
{
    if ( gm == NULL )
        return 1;

    if ( gm->stage.render != NULL )
        gm->stage.render( gm );

    gm->frame_count++;

    return 0;
}

static int internal_loop_( struct game *gm )
{
    log_debug( "Starting game loop..." );
    internal_init_( gm );

    uint64_t frame_previous = SDL_GetTicks();
    double tick_time = 0;

    uint64_t tick_last = 0;
    uint64_t frame_last = 0;

    uint64_t frame_timer = frame_previous;

	// begin main loop
    while ( gm->running )
    {
        // get frame timing
        uint64_t frame_current = SDL_GetTicks();
        uint64_t frame_delta = frame_current - frame_previous;

        // update fps & tps every second
        if ( frame_current - frame_timer >= 1000 )
        {
            // get variables
            uint64_t ticks  = gm->tick_count - tick_last;
            uint64_t frames = gm->frame_count - frame_last;

            // store rate per second
            gm->frame_rate = frames;
            gm->tick_rate = ticks;

            // store this frame/tick
            tick_last  = gm->tick_count;
            frame_last = gm->frame_count;

            // reset timer
            frame_timer = frame_current;
        }

        frame_previous = frame_current;
        tick_time += frame_delta;

        // poll events
        if ( input_process_events() != 0 )
            goto soft_exit_;
        
        // maintain fixed time step for each tick
        while ( tick_time >= gm->tick_target )
        {
            internal_tick_( gm );
            tick_time -= gm->tick_target;
        }

        internal_update_( gm );
        internal_render_( gm );

        // calculate & store frame time
        gm->frame_delta = ( double ) frame_delta / 1000.0;

        // apply fps cap
        int delay = frame_current + gm->frame_target - SDL_GetTicks();
        if ( delay > 0 )
            SDL_Delay( delay );
    }

soft_exit_:
	internal_free_( gm );
    return 0;
}

int game_init( struct game *gm, struct stage state )
{
	gm->stage        = state;
    gm->running      = false;

	gm->frame_delta  = 0;
	gm->frame_target = 1000.0 / 60.0;
	gm->frame_rate   = 0;
	gm->frame_count  = 0;

	gm->tick_delta   = 0;
	gm->tick_target  = 1000.0 / 30.0;
	gm->tick_rate    = 0;
	gm->tick_count   = 0;

	return 0;
}

void game_loop( struct game *gm )
{
    if ( gm == NULL )
        return;

    gm->running = true;
    internal_loop_( gm );
}

void game_stop( struct game *gm )
{
    gm->running = false;
}

void game_set_target_fps( struct game *gm, double target )
{
    gm->frame_target = target <= 0.0 ? 0.0 : 1000.0 / target;
}

void game_set_target_tps( struct game *gm, double target )
{
    gm->tick_target = target <= 0.0 ? 0.0 : 1000.0 / target;
}

uint64_t game_get_fps( struct game *gm )
{
    return gm->frame_rate;
}

uint64_t game_get_tps( struct game *gm )
{
    return gm->tick_rate;
}
