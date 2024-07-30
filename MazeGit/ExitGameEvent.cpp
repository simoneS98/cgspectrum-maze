#include "ExitGameEvent.h"

ExitGameEvent::ExitGameEvent()
{
}

bool ExitGameEvent::Activate(Game* game)
{
	system("cls");
	std::cout << "Esc was pressed! Exiting game..." << std::endl;
	exit(0);
	return true;
}
