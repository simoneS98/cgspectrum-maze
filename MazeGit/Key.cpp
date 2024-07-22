#include <iostream>
#include "windows.h"

#include "Key.h"

Key::Key(int x, int y, Room* pRoom, Color color)
	: GameEntity(x, y, pRoom, color)
{
	type = EntityType::PASSIVE;
}

void Key::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)color);

	std::cout << keySprite;

	SetConsoleTextAttribute(console, (int)cDefaultColor);
}


bool Key::CollideWith(GameEntity* collidedEntity)
{
	return collidedEntity->TryPickupKey(this);
}
