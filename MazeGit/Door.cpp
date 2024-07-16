#include "Door.h"
#include <iostream>
#include <Windows.h>

Door::Door(int x, int y, Color closedColor, Color openColor) :
	GameEntity::GameEntity(x,y,openColor)
	, isLocked(true)
	, closedColor((int)closedColor)
{
}

/*
void Door::Unlock()
{
	if (isLocked)
		isLocked = false;
}
*/
Color Door::GetColor() { return Color(closedColor); }

void Door::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	if(isLocked)
		SetConsoleTextAttribute(console, closedColor);
	else
		SetConsoleTextAttribute(console, color);

	std::cout << cDoorSprite;
	SetConsoleTextAttribute(console, cDefaultColor);
}
