#pragma once

#include "Game.h"

#define MAP_ROW_NUMBER 20
#define MAP_COLUMN_NUMBER 25

#define TILE_SIZE 32

class Map
{
public:
	Map();
	~Map();

	void LoadMap(int array[MAP_ROW_NUMBER][MAP_COLUMN_NUMBER]);
	void DrawMap();

private:
	SDL_Rect src_rect, dest_rect;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[MAP_ROW_NUMBER][MAP_COLUMN_NUMBER];
};

