#include "Options.h"
#include <conio.h>

Input Options::GetUserInput()
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

Options::Options(std::vector<MenuOption> options)
    : m_options(options)
    , m_selectedIndex(0)
{
}

void Options::Update()
{
    Input userInput = GetUserInput();
    if (userInput == Input::NONE)
        return;

    int currIndex = m_selectedIndex;
    // GetUserInput returns UP or DOWN
    if (userInput == Input::ARROW_DOWN)
        m_selectedIndex = (currIndex + 1) % (m_options.size());
    else if (userInput == Input::ARROW_UP)
        m_selectedIndex = (currIndex == 0 ? m_options.size() - 1 : currIndex - 1);
    else if (userInput == Input::ENTER)
        m_options[currIndex].Select();

    return;
}

void Options::Draw()
{
    for (int i = 0; i < m_options.size(); i++)
    {
        if (m_selectedIndex == i)
            std::cout << "-> ";
        std::cout << m_options[i] << std::endl;
    }
}