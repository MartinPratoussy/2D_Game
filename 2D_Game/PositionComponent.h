#pragma once

#include "Components.h"

class PositionComponent : public Component
{
private:
	int pos_x;
	int pos_y;

public:
	PositionComponent()
	{
		pos_x = 0;
		pos_y = 0;
	}

	PositionComponent(int x, int y)
	{
		pos_x = x;
		pos_y = y;
	}

	int x() { return pos_x; }
	int y() { return pos_y; }

	void init() override
	{
		pos_x = 0;
		pos_y = 0;
	}

	void update() override
	{
		pos_x++;
		pos_y++;
	}

	void setPos(int x, int y)
	{
		pos_x = x;
		pos_y = y;
	}
};