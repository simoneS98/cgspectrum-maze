#include "ScoreMenuState.h"
#include <iostream>
#include "LevelManager.h"
#include <thread>
#include <fstream>
#include "EventManager.h"
#include "ExitGameEvent.h"

ScoreMenuState::ScoreMenuState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
{
}

bool ScoreMenuState::LoadScoresForLevel(std::string levelName)
{
    if (levelName.empty())
    {
        system("cls");
        std::cout << "[ScoreMenu] Level not set!" << std::endl;
        
        return false;
    }

    std::ifstream levelFile;

    std::string fileName = levelName + "/leaderboard.txt";

    std::string fileContent = ReadFile(fileName);

    std::string delimiter = ">=";

    size_t pos = 0;
    std::string token;
    while ((pos = fileContent.find(delimiter)) != std::string::npos) {
        token = fileContent.substr(0, pos);
        std::cout << token << std::endl;
        fileContent.erase(0, pos + delimiter.length());
    }
    std::cout << fileContent << std::endl;

    char c;
    std::cin >> c;

    /*levelFile.open(fileName);

    if (!levelFile)
    {
        std::cout << "[ScoreMenu] Opening leaderboard.txt failed!" << std::endl;
        return false;
    }
    else
    {
        if (levelFile.is_open())
        {
            std::string content;

            std::string line;

            getline(levelFile, line);

            int width = stoi(line);

            getline(levelFile, line);

            height = stoi(line);

            getline(levelFile, line);

            //TODO: fix file parsing
            int size = width * height + 1;

            // copying the contents of the 
            // string to char array
            strcpy_s(mapAsCharArray, size, line.c_str());



            //delete[] mapAsCharArray;
            //mapAsCharArray = nullptr;

            levelFile.close();
        }

        levelFile.close();
    }*/
}

void ScoreMenuState::Enter()
{
    bool loadSuccessful = true;

    loadSuccessful = LoadScoresForLevel(LevelManager::GetInstance()->GetLevelName());

    auto waitBeforeExitingToMainMenu = [&](int seconds) {

        std::this_thread::sleep_for(std::chrono::milliseconds(seconds * 1000));

        EventManager::GetInstance()->Add(new ExitGameEvent("Load completed???"));
    };

    if (!loadSuccessful)
    {
        std::cout << "Exiting to main menu..." << std::endl;
        std::thread waitThread(waitBeforeExitingToMainMenu, 3);
        waitThread.join();
    }
}

void ScoreMenuState::Exit()
{
}

bool ScoreMenuState::Update(bool processInput)
{
    return false;
}

void ScoreMenuState::Draw()
{
    
        
    // TODO: save info on ExitReachedEvent?
    // save/load player info on file
    //m_pOwner->
}
