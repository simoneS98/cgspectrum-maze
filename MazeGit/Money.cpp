#include "Money.h"
#include <iostream>

Money::Money(int x, int y, int worth)
	: GameEntity(x,y, Color::GREEN_MONEY)
	, worth(worth)
{
}

void Money::Draw()
{
	std::cout << cMoneySprite;
}