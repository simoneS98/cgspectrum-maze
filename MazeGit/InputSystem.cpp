#include "InputSystem.h"
#include <conio.h>

Input InputSystem::GetInput()
{
    int intInput = _getch();
    Input input = Input::NONE;

    //check if an arrow key was pressed
    if (intInput == (int)Input::ARROW_IN)
    {
        //read actual arrow value
        int arrowInput = _getch();

        switch (arrowInput)
        {
        case (int)Input::ARROW_DOWN:
        case (int)Input::ARROW_RIGHT:
            input = Input::ARROW_DOWN;
            break;
        case (int)Input::ARROW_UP:
        case (int)Input::ARROW_LEFT:
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
    else if (intInput == (int)Input::LIST_END)
    {
        input = Input::LIST_END;
    }
    // TODO: add quit() to scoremenustate
    else if (intInput == (int)Input::ESC || intInput == (int)Input::QUIT)
    {
        input = Input::ESC;
    }

    return input;
}
