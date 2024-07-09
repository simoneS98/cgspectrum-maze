#include "Level.h"
#include <iostream>
#include "FileUtils.h"

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
Level::Level()
{

}

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

bool Level::Load(std::string filename)
{
	try
	{
		Level level = FileUtils::FileToLevel(filename);
	}
}

void Level::DisplayLeftBorder()
{
	DisplayVerticalBorder();
}

void Level::DisplayRightBorder()
{
	DisplayVerticalBorder();
	std::cout << std::endl;
}

void Level::DisplayVerticalBorder()
{
	std::cout << (char)RoomContent::WALL;
}

void Level::DisplayHorizontalBorder()
{
	// -1 and +1 to take care of left and right corners
	for (int i = -1; i < width + 1; i++)
	{
		std::cout << (char)RoomContent::WALL;
	}

	std::cout << std::endl;
}