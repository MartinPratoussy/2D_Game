#include "Map.h"
#include "Game.h"

#include <fstream>

Map::Map()
{
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int size_x, int size_y)
{
	char c;
	std::fstream map_file;
	map_file.open(path);

	int src_x, src_y;

	for (int y = 0; y < size_y; y++)
	{
		for (int x = 0; x < size_x; x++)
		{
			map_file.get(c);
			src_y = atoi(&c) * 32;

			map_file.get(c);
			src_x = atoi(&c) * 32;

			Game::AddTile(src_x, src_y, x * 64, y * 64);
			map_file.ignore();
		}
	}


	map_file.close();
}
