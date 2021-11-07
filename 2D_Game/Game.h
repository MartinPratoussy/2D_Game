#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int pos_x, int pos_y, int width, int height, bool fullscreen);

	void handle_events();
	void update();
	void render();
	void clean();

	static void AddTile(int src_x, int src_y, int pos_x, int pos_y);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;
	static bool is_running;

private:
	SDL_Window *window_;
};

