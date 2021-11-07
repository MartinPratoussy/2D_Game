#pragma once

#include <SDL.h>

#include "Components.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect src_rect, dest_rect;
	
	TileComponent() = default;

	~TileComponent ()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int src_x, int src_y, int pos_x, int pos_y, const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		src_rect.x = src_x;
		src_rect.y = src_y;
		src_rect.w = src_rect.h = 32;

		dest_rect.x = pos_x;
		dest_rect.y = pos_y;
		dest_rect.w = dest_rect.h = 64;
	}

	void draw() override
	{
		TextureManager::Draw(texture, src_rect, dest_rect, SDL_FLIP_NONE);
	}
};