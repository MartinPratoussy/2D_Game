#pragma once

#include <SDL.h>
#include <stdio.h>
#include <iostream>

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

	bool running() const { return isRunning; }

private:
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer * renderer;
};

