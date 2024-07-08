#include "Level.h"

/*
void Level::SetWidth(int width)
{
	this->width = width;
}

void Level::SetHeight(int height)
{
	this->height = height;
}
*/

Level::Level(Room** map, int width, int height)
{
	this->map = map;
	this->width = width;
	this->height = height;
}

int Level::GetWidth()
{
	return width;
}

int Level::GetHeight()
{
	return height;
}

int Level::GetSize()
{
	return width * height;
}

Room* Level::GetRoom(int x, int y)
{
	int index = GetIndexFromXY(x, y);
	return map[index];
}

Room** Level::GetMap()
{
	return map;
}

int Level::GetIndexFromXY(int x, int y)
{
	return x * width + y;
}
