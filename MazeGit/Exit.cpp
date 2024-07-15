#include "Exit.h"
#include <iostream>

Exit::Exit(int x, int y, std::string fileName) : GameEntity::GameEntity(x, y)
{
	this->nextRoomFileName = fileName;
	this->nextRoom = nullptr;
}

void Exit::Draw()
{
	std::cout << sprite;
}
