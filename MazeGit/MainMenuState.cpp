#include "MainMenuState.h"
#include <iostream>
#include <conio.h>

MainMenuState::MainMenuState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
{
    m_MenuOptions = {
        MenuOption("Start New Game", new StartGameEvent(pOwner)),
        MenuOption("Load Game", nullptr),
        MenuOption("Leaderboard", nullptr),
        MenuOption("Exit", new ExitGameEvent())
    };
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
    Input userInput = GetUserInput();
    if (userInput == Input::NONE)
        return false;
    // GetUserInput returns UP or DOWN
    int newIndex = m_SelectedIndex;

    if (userInput == Input::ARROW_DOWN)
        newIndex = (m_SelectedIndex + 1) % (m_MenuOptions.size());
    else if (userInput == Input::ARROW_UP)
        newIndex = (newIndex == 0 ? m_MenuOptions.size() - 1 : newIndex - 1);
    else if (userInput == Input::ENTER)
        m_MenuOptions[m_SelectedIndex].Select();
    //m_MenuOptions[m_SelectedIndex].Deselect();
    //m_MenuOptions[newIndex].Select();
    m_SelectedIndex = newIndex;
    return false;
}

void MainMenuState::Draw()
{
    system("cls");
    DisplayOptions();
}

bool MainMenuState::Load()
{
    return false;
}

void MainMenuState::DisplayOptions()
{
    /*
    for (auto menuOption = m_MenuOptions.begin(); menuOption != m_MenuOptions.end(); ++menuOption)
    {
        if (menuOption->IsSelected())
            std::cout << "→";
        std::cout << (*menuOption);
    }
    */
    std::cout << m_SelectedIndex << std::endl;
    
    for (int i = 0; i < m_MenuOptions.size(); i++)
    {
        if(m_SelectedIndex==i)
            std::cout << "-> ";
        std::cout << m_MenuOptions[i] << std::endl;
    }
    
}

Input MainMenuState::GetUserInput()
{
    int intInput = _getch();
    Input input = Input::NONE;
    //int intInput = GetRoomChoice();

    //check if an arrow key was pressed
    if (intInput == (int)Input::ARROW_IN)
    {
        //read actual arrow value
        int arrowInput = _getch();

        switch (arrowInput)
        {
        case (int)Input::ARROW_DOWN:
            input = Input::ARROW_DOWN;
            break;
        case (int)Input::ARROW_UP:
            input = Input::ARROW_UP;
            break;
        default:
            break;
        }
    }
    else if (intInput == (int)Input::ENTER)
    {
        input = Input::ENTER;
    }

    return input;
}

std::ostream& operator<<(std::ostream& os, const MenuOption& menuOption)
{
    return os << menuOption.m_Title;
}
