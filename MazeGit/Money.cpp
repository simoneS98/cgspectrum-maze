#include "Money.h"
#include <iostream>

Money::Money(int x, int y, Room* pRoom, int worth)
	: GameEntity(x,y, pRoom, Color::GREEN_MONEY)
	, worth(worth)
{
}

void Money::Draw()
{
	std::cout << cMoneySprite;
}

bool Money::CollideWith(GameEntity* collidedEntity)
{
	collidedEntity->PickupMoney(this);
	return true;
}
