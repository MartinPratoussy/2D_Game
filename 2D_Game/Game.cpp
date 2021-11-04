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

		window_ = SDL_CreateWindow(title, pos_x, pos_y, width, height, flags);
		if (window_) std::cout << "Window created!" << std::endl;

		renderer_ = SDL_CreateRenderer(window_, -1, 0);
		if (renderer_) std::cout << "Renderer created!" << std::endl;

		is_running_ = true;
	}
	else {
		is_running_ = false;
	}
}

void Game::handle_events()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		is_running_ = false;
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
	SDL_RenderClear(renderer_);

	// Space for rendering

	SDL_RenderPresent(renderer_);
}

void Game::clean()
{
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}