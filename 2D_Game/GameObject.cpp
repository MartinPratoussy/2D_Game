#include "GameObject.h"

GameObject::GameObject(const char* texture_sheet)
{
	obj_texture_ = TextureManager::LoadTexture(texture_sheet);
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	pos_x_++;
	pos_y_++;

	src_rect_.h = 32;
	src_rect_.w = 32;
	src_rect_.x = 0;
	src_rect_.y = 0;

	dest_rect_.x = pos_x_;
	dest_rect_.y = pos_y_;
	dest_rect_.w = src_rect_.w * 2;
	dest_rect_.h = src_rect_.h * 2;
}

void GameObject::render()
{
	SDL_RenderCopy(Game::renderer, obj_texture_, &src_rect_, &dest_rect_);
}
