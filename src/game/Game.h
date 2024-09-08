#ifndef GAME_H
#define GAME_H

class Game
{
public:
	void Init( void );
	void Free( void );
	void Tick( void );
	void Update( void );
	void Render( void );
};

extern Game *game;

#endif
