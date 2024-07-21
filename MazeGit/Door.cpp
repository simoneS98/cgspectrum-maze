#include "Door.h"
#include <iostream>
#include <Windows.h>

Door::Door(int x, int y,Color openColor) :
	GameEntity::GameEntity(x,y,openColor)
	, isLocked(true)
	, openColor((int)Color::DOOR_OPEN)
{
}

/*
void Door::Unlock()
{
	if (isLocked)
		isLocked = false;
}
*/
Color Door::GetColor() { return Color(color); }

bool Door::HandleCollision(GameEntity* collidedEntity)
{
	return collidedEntity->TryUseKeyOn(this);
}

void Door::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	if(isLocked)
		SetConsoleTextAttribute(console, color);
	else
		SetConsoleTextAttribute(console, openColor);

	std::cout << cDoorSprite;
	SetConsoleTextAttribute(console, cDefaultColor);
}
