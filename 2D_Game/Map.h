#pragma once

#include <string>

#define MAP_ROW_NUMBER 20
#define MAP_COLUMN_NUMBER 25

#define TILE_SIZE 32

class Map
{
public:
	Map();
	~Map();

	static void LoadMap(std::string path, int size_x, int size_y);

private:
};

