#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char * title, int pos_x, int pos_y, int width, int height, bool fullscreen)
{

	const int flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		std::cout << "Subsystems initialized!" << std::endl;

		window = SDL_CreateWindow(title, pos_x, pos_y, width, height, flags);
		if (window) std::cout << "Window created!" << std::endl;

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) std::cout << "Renderer created!" << std::endl;

		isRunning = true;
	}
	else {
		isRunning = false;
	}
}

void Game::handle_events()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update()
{
}

void Game::render()
{
	SDL_RenderClear(renderer);

	// Space for rendering

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}