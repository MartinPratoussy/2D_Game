#include "Game.h"

#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

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

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/player.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
}

void Game::handle_events()
{
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

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, 
		wall.getComponent<ColliderComponent>().collider)) 
	{
		player.getComponent<TransformComponent>().velocity * -1;
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