#include "ScoreMenuState.h"
#include <iostream>
#include "LevelManager.h"
#include <thread>
#include <fstream>
#include "LoadLevelScoresEvent.h"

using Option = Options::MenuOption;

ScoreMenuState::ScoreMenuState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
    , m_savedGames({})
{
}


void ScoreMenuState::Enter()
{
    // uniform initialization
    // equals to sandbox = std::filesystem::path("...")
    const std::filesystem::path levelsPath{ "../levels" };
    for (auto const& dir_entry : std::filesystem::directory_iterator{ levelsPath })
    {
        if (dir_entry.is_directory())
        {
            std::string levelName = dir_entry.path().filename().string();
            m_savedGames.Add(
                Option(
                    levelName,
                    new LoadLevelScoresEvent(levelName/*levelName.c_str()*/)
                )
            );
        } 
    }

    /*
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
    */
    
}

void ScoreMenuState::Exit()
{
}

bool ScoreMenuState::Update(bool processInput)
{
    m_savedGames.Update();
    return false;
}

void ScoreMenuState::Draw()
{
    system("cls");
    m_savedGames.Draw();
}