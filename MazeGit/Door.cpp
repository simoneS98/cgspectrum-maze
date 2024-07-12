#include "Door.h"
#include <iostream>

Door::Door(int x, int y, std::string fileName) : GameEntity::GameEntity(x,y)
{
	this->nextRoomFileName = fileName;
	this->isLocked = true;
	this->nextRoom = nullptr;
}

void Door::Unlock()
{
	if (isLocked)
		isLocked = false;
}

void Door::Draw()
{
	std::cout << sprite;
}
