#include "ScoreMenuState.h"
#include <iostream>
#include "LevelManager.h"
#include <thread>
#include <fstream>
#include "LevelChosenEvent.h"

using Option = Options::MenuOption;

ScoreMenuState::ScoreMenuState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
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
                    new LevelChosenEvent(levelName)//LoadLevelScoresEvent(levelName/*levelName.c_str()*/)
                )
            );
        } 
    }

    Draw();
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
    std::cout << "Choose a level to show its leaderboard: " << std::endl << std::endl;
    m_savedGames.Draw();
}