#include <iostream>
#include "windows.h"

#include "Key.h"

Key::Key(int x, int y, Color color)
	: GameEntity(x, y, color)
{
}

void Key::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)color);

	std::cout << keySprite;

	SetConsoleTextAttribute(console, (int)cDefaultColor);
}


bool Key::HandleCollision(GameEntity* collidedEntity)
{
	return collidedEntity->TryPickupKey(this);
}
