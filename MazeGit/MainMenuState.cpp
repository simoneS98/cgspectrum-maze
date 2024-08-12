#include "MainMenuState.h"
#include <iostream>
#include <conio.h>

using Option = Options::MenuOption;

MainMenuState::MainMenuState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
    // uniform init for Options constructor 
    , m_options({
        Option("Start New Game", new StartGameEvent()),
        Option("Resume Game", nullptr),
        Option("Leaderboard", new ShowLeaderboardEvent()),
        Option("Exit", new ExitGameEvent("Esc was pressed! Exiting game..."))
        })
{
}

void MainMenuState::Enter()
{
    Draw();
}

void MainMenuState::Exit()
{
}

bool MainMenuState::Update(bool processInput)
{
    m_options.Update();
    return false;
}

void MainMenuState::Draw()
{
    system("cls");
    m_options.Draw();
}

bool MainMenuState::Load()
{
    return false;
}