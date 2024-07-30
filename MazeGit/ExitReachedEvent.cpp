#include "ExitReachedEvent.h"

ExitReachedEvent::ExitReachedEvent()
{
}

bool ExitReachedEvent::Activate(Game* game)
{
    system("cls");
    std::cout << "Congrats! You exited the maze!" << std::endl;
    exit(0);
    return true;
}
