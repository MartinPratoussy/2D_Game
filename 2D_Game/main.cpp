#include "Game.h"

Game* game = nullptr;

int main(int args, char *argv[])
{
	const int FPS = 165;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("2D_Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (Game::is_running) {

		std::cout << "Game is running..." << std::endl;

		frameStart = SDL_GetTicks();

		game->handle_events();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}

	game->clean();

	return 0;
}