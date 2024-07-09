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
Level::Level()
{
}
*/
Level::Level()
	: map(nullptr)
	, height(0)
	, width(0)
{

}

Level::~Level()
{
	if (map != nullptr)
	{
		delete[] map;
		map = nullptr;
	}
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
    std::ifstream levelFile;

    filename.insert(0, "../");

    levelFile.open(filename);

    if (!levelFile)
    {
        std::cout << "Opening file failed!" << std::endl;
        return false;
    }
    else
    {
        if (levelFile.is_open())
        {
            std::string line;

            getline(levelFile, line);

            width = stoi(line);

            getline(levelFile, line);

            height = stoi(line);

            getline(levelFile, line);

            //TODO: fix file parsing
            int size = width * height + 1;

            // declaring character array (+1 for null terminator) 
            char* mapAsCharArray = new char[size];
            map = new Room * [size];

            // copying the contents of the 
            // string to char array
            strcpy_s(mapAsCharArray, size, line.c_str());

            for (int i = 0; i < size; i++)
            {
                map[i] = RoomFactory::make(RoomContent(mapAsCharArray[i]));
            }

            delete[] mapAsCharArray;
            mapAsCharArray = nullptr;

            levelFile.close();
        }

        levelFile.close();
    }

    if (map == nullptr)
        return false;

    return true;
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