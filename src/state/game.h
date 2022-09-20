#ifndef GAME_H
#define GAME_H

// make frame and tick rate the same so i don't have to worry about interpolation
#define DEFAULT_FRAME_RATE			60
#define DEFAULT_TICK_RATE			60

#define DEFAULT_WINDOW_WIDTH		700
#define DEFAULT_WINDOW_HEIGHT		700

int game_init( void );
int game_free( void );
int game_update( void );
int game_tick( void );
int game_render( void );

#endif
