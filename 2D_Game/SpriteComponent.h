#pragma once

#include <SDL.h>

#include "Components.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent *transform_;
	SDL_Texture *texture_;
	SDL_Rect src_rect, dest_rect;

public:
	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture_);
	}

	void setTexture(const char* path)
	{
		texture_ = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		transform_ = &entity->getComponent<TransformComponent>();

		src_rect.x = src_rect.y = 0;

		src_rect.w = transform_->width;
		src_rect.h = transform_->height;

		dest_rect.w = transform_->width * transform_->scale;
		dest_rect.h = transform_->height * transform_->scale;
	}

	void update() override
	{
		dest_rect.x = static_cast<int>(transform_->position.x);
		dest_rect.y = static_cast<int>(transform_->position.y);
		dest_rect.w = transform_->width * transform_->scale;
		dest_rect.h = transform_->height * transform_->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture_, src_rect, dest_rect);
	}

};