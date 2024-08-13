#include "LevelManager.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <Constants.h>
#include <filesystem>


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
    int h = 0;

    char* map = m_pCurrentRoom->RevertToCharMap();

    std::string basePath = "levels/" + m_levelName + "/saves/";// +currentRoom->GetName() + ".room";

    // this is working directory for the current level
    basePath.insert(0, "../");

    std::string cmd = "mkdir \"" + basePath + "\"";

    //cmd.append(levelName).append("\"");

    system(cmd.c_str());

    std::string fileName = basePath + m_pCurrentRoom->GetName() + ".room";

    // TODO: fix save dir

    std::ofstream levelFile;
    levelFile.open(fileName);

    if (!levelFile)
    {
        std::cout << "Saving room state failed!" << std::endl;
    }
    else
    {
        levelFile << cMaxRoomWidth << std::endl;
        levelFile << cMaxRoomHeight << std::endl;
        //levelFile << "level=";
        for (int i = 0; i < cMaxRoomWidth * cMaxRoomHeight; i++)
        {
            levelFile << map[i];
        }
        levelFile << std::endl;
        //levelFile.write(level->map, level->width * level->height); //width * height : streamsize
        if (!levelFile)
        {
            std::cout << "Write failed!" << std::endl;
        }
        levelFile.close();
    }
}

bool LevelManager::Load(std::string roomName)
{
    int width = 0;
    int height = 0;
    Room** map;
    std::ifstream levelFile;

    std::string fileName = "../levels/" + m_levelName + "/saves/"  + roomName + ".room";

    char* mapAsCharArray = nullptr;

    // saves dir not found
    if (!std::filesystem::exists(fileName))
    {
        // load the base level file
        fileName = "../levels/" + m_levelName + "/" + roomName + ".room";
    }

    levelFile.open(fileName);

    if (!levelFile)
    {
        std::cout << "Opening level file failed!" << std::endl;
        return false;
    }

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
        //char mapAsCharArray[size]
        map = new Room * [size];

        // copying the contents of the 
        // string to char array
        strcpy_s(mapAsCharArray, size, line.c_str());

        //delete[] mapAsCharArray;
        //mapAsCharArray = nullptr;

        levelFile.close();
    }

    if (mapAsCharArray == nullptr)
        return false;

    
     if (m_pCurrentRoom != nullptr)
    {
        delete m_pCurrentRoom;
        m_pCurrentRoom = nullptr;
    }
    
    m_pCurrentRoom = new Room(width, height, mapAsCharArray, roomName);

    return true;
}