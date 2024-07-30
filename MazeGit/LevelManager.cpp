#include "LevelManager.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include "Room.h"


LevelManager* LevelManager::instance = nullptr;

void LevelManager::Remove()
{
}

LevelManager* LevelManager::GetInstance()
{
   	if (instance == nullptr)
		instance = new LevelManager();
	return instance;
}

void LevelManager::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

void LevelManager::Save()
{
}

bool LevelManager::Load(std::string roomName)
{
    int width = 0;
    int height = 0;
    Room** map;
    std::ifstream levelFile;

    std::string fileName = levelName + "/" + roomName + ".room";//levelName.append("/").append(roomName).append(".room");

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

    if (currentRoom != nullptr)
    {
        delete currentRoom;
        currentRoom = nullptr;
    }

    currentRoom = new Room(width, height, mapAsCharArray, roomName);

    return true;
}
