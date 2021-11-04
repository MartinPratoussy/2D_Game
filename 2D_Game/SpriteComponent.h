#pragma once

#include <SDL.h>

#include "Components.h"

class SpriteComponent : public Component
{
private:
	PositionComponent *position_;
	SDL_Texture *texture_;
	SDL_Rect src_rect, dest_rect;

public:
	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	void setTexture(const char* path)
	{
		texture_ = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		position_ = &entity->getComponent<PositionComponent>();

		src_rect.x = src_rect.y = 0;
		src_rect.w = src_rect.h = 32;

		dest_rect.w = dest_rect.h = 64;
	}

	void update() override
	{
		dest_rect.x = position_->x();
		dest_rect.y = position_->y();
	}

	void draw() override
	{
		TextureManager::Draw(texture_, src_rect, dest_rect);
	}

};