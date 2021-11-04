#include <SDL.h>

#include "Game.h"

Game* game = nullptr;

int main(int args, char *argv[])
{
	game = new Game();
	game->init("2D_Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, false);

	while (game->running()) {
		game->handle_events();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}