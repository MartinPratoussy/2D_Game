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

std::vector<ColliderComponent*> Game::colliders;

bool Game::is_running = false;

auto& player(manager.addEntity());

const char* map_file = "assets/terrain_texture.png";

enum group_labels : std::size_t
{
	group_maps,
	group_players,
	group_enemies,
	group_colliders
};

auto& tiles(manager.GetGroup(group_maps));
auto& players(manager.GetGroup(group_players));
auto& enemies(manager.GetGroup(group_enemies));
auto& colliders(manager.GetGroup(group_colliders));

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

		is_running = true;
	}
	else {
		is_running = false;
	}

	Map::LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/player_anims.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(group_players);
}

void Game::handle_events()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		is_running = false;
		break;

	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	Vector2D player_velocity = player.getComponent<TransformComponent>().velocity;
	int player_speed = player.getComponent<TransformComponent>().speed;

	for (auto t : tiles)
	{
		t->getComponent<TileComponent>().dest_rect.x += -(player_velocity.x * player_speed);
		t->getComponent<TileComponent>().dest_rect.y += -(player_velocity.y * player_speed);
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles) t->draw();
	for (auto& p : players) p->draw();
	for (auto& e : enemies) e->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}

void Game::AddTile(int src_x, int src_y, int pos_x, int pos_y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(src_x, src_y, pos_x, pos_y, map_file);
	tile.addGroup(group_maps);
}
