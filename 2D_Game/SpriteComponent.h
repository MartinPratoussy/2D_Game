#pragma once

#include <SDL.h>
#include <map>

#include "Components.h"
#include "TextureManager.h"
#include "Animation.h"

class SpriteComponent : public Component
{
private:
	TransformComponent *transform_;
	SDL_Texture *texture_;
	SDL_Rect src_rect_, dest_rect_;

	bool animated_ = false;
	int frames_ = 0;
	int speed_ = 100;

public:

	int anim_index = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	SpriteComponent(const char* path, bool is_animated) 
	{
		animated_ = is_animated;

		Animation idle = Animation(0, 2, 100);
		Animation walk = Animation(1, 4, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		play("Idle");
		
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

		src_rect_.x = src_rect_.y = 0;

		src_rect_.w = transform_->width;
		src_rect_.h = transform_->height;

		dest_rect_.w = transform_->width * transform_->scale;
		dest_rect_.h = transform_->height * transform_->scale;
	}

	void update() override
	{
		if (animated_)
		{
			src_rect_.x = src_rect_.w * static_cast<int>((SDL_GetTicks() / speed_) % frames_);
		}

		src_rect_.y = anim_index * transform_->height;

		dest_rect_.x = static_cast<int>(transform_->position.x);
		dest_rect_.y = static_cast<int>(transform_->position.y);
		dest_rect_.w = transform_->width * transform_->scale;
		dest_rect_.h = transform_->height * transform_->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture_, src_rect_, dest_rect_, sprite_flip);
	}

	void play(const char* anim_name)
	{
		frames_ = animations[anim_name].frames;
		anim_index = animations[anim_name].index;
		speed_ = animations[anim_name].speed;
	}

};