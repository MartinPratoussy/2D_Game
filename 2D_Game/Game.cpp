#include "Game.h"

#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());

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

		renderer = SDL_CreateRenderer(window_, -1, 0);
		if (renderer) std::cout << "Renderer created!" << std::endl;

		is_running_ = true;
	}
	else {
		is_running_ = false;
	}

	map = new Map();

	player.addComponent<TransformComponent>(100, 500);
	player.addComponent<SpriteComponent>("assets/player.png");

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
	manager.refresh();
	manager.update();

	player.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));

	if (player.getComponent<TransformComponent>().position.x > 100)
	{
		player.getComponent<SpriteComponent>().setTexture("assets/enemy.png");
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	map->DrawMap();

	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}