#include "Game.h"

int main()
{
	Game* game = new Game();
	while (Game::run){
		game->Update();
    }
	return 0;
}