#ifndef GAME_H
#define GAME_H

class game
{
public:
	game( void );
	void start( void );

	int init( void );
	int free( void );
	int tick( void );
	int update( void );
	int render( void );
};

#endif
