#ifndef GAME_H
#define GAME_H

class Game
{
public:
	void Init( void );
	void Free( void );
	void Tick( void );
	void Step( void );
	void Draw( void );
};

extern Game *game;

#endif
