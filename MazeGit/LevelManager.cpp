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

void LevelManager::SaveRoomState(bool createTmpFile)
{
    int h = 0;

    char* map = m_pCurrentRoom->RevertToCharMap();

    std::string fileName;

    if (createTmpFile)
    {
        fileName = "../levels/" + m_levelName + "/.tmp.room";
    }
    else
    {
        std::string basePath = "../levels/" + m_levelName + "/saves/";
        std::string cmd = "mkdir \"" + basePath + "\"";
        system(cmd.c_str());
        fileName = basePath + m_pCurrentRoom->GetName() + ".room";
    }

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

    std::string fileName;

    std::string fileNameResumeGame = "../levels/" + m_levelName + "/.tmp.room";
    std::string fileNameSavedGame = "../levels/" + m_levelName + "/saves/" + roomName + ".room";
    std::string fileNameBaseGame = "../levels/" + m_levelName + "/" + roomName + ".room";

    char* mapAsCharArray = nullptr;

    // check .tmp file
    if (std::filesystem::exists(fileNameResumeGame))
        fileName = fileNameResumeGame;
    // check saves dir
    else if (std::filesystem::exists(fileNameSavedGame))
        fileName = fileNameSavedGame;
    // check base dir
    else if (std::filesystem::exists(fileNameBaseGame))
        fileName = fileNameBaseGame;
    else // no useful files found
        return false;
    
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