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
	char tile;
	std::fstream map_file;
	map_file.open(path);

	for (int y = 0; y < size_y; y++)
	{
		for (int x = 0; x < size_x; x++)
		{
			map_file.get(tile);
			Game::AddTile(atoi(&tile), x * TILE_SIZE, y * TILE_SIZE);
			map_file.ignore();
		}
	}


	map_file.close();
}
