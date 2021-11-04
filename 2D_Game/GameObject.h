#pragma once

#include "Game.h"

class GameObject
{
public:
	GameObject(const char* texture_sheet);
	~GameObject();

	void update();
	void render();

private:
	int pos_x_ = 0;
	int pos_y_ = 0;

	SDL_Texture* obj_texture_;
	SDL_Rect src_rect_, dest_rect_;
};

