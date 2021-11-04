#include "TextureManager.h"

SDL_Texture * TextureManager::LoadTexture(const char * filename)
{
	SDL_Surface* tmp_surface = IMG_Load(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);

	return texture;
}

void TextureManager::Draw(SDL_Texture * texture, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}
