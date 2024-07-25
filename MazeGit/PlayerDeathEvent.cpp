#include "PlayerDeathEvent.h"
#include <stdlib.h>
#include <iostream>

PlayerDeathEvent::PlayerDeathEvent()
	: Event()
{
}

bool PlayerDeathEvent::Activate()
{
	system("cls");
	std::cout << "No more lives left! GAME OVER" << std::endl;
	exit(0);
	return true;
}
