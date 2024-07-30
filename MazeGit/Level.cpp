#include "Level.h"
#include <iostream>
#include "FileUtils.h"

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

    if (currentRoom != nullptr)
    {
        delete currentRoom;
        currentRoom = nullptr;
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

Room* Level::GetCurrentRoom()
{
    return currentRoom;
}

Room** Level::GetMap()
{
	return map;
}

int Level::GetIndexFromXY(int x, int y)
{
	return x * width + y;
}

/*
bool Level::Load(std::string levelName, std::string roomName)
{
    if (currentRoom != nullptr)
    {
        delete currentRoom;
        currentRoom = nullptr;
    }

    std::ifstream levelFile;

    std::string fileName = levelName.append("/").append(roomName).append(".room");

    char* mapAsCharArray = nullptr;

    // this is working directory for the current level
    fileName.insert(0, "../levels/");

    std::cout << "Trying to open file " << fileName << std::endl;

    levelFile.open(fileName);

    if (!levelFile)
    {
        std::cout << "Opening level file failed!" << std::endl;
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
            mapAsCharArray = new char[size];
            map = new Room * [size];

            // copying the contents of the 
            // string to char array
            strcpy_s(mapAsCharArray, size, line.c_str());

            

            //delete[] mapAsCharArray;
            //mapAsCharArray = nullptr;

            levelFile.close();
        }

        levelFile.close();
    }

    if (mapAsCharArray == nullptr)
        return false;

    currentRoom = new Room(width, height, mapAsCharArray);

    return true;
}
*/
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
	std::cout << (char)Sprite::WALL;
}

void Level::DisplayHorizontalBorder()
{
	// -1 and +1 to take care of left and right corners
	for (int i = -1; i < width + 1; i++)
	{
		std::cout << (char)Sprite::PERIMETER;
	}

	std::cout << std::endl;
}

void Level::Draw()
{
    //DisplayHorizontalBorder();
    currentRoom->Draw();
    //DisplayHorizontalBorder();
}