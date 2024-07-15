#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int x, int y, int maxHp, int deltaX, int deltaY, int damage)
	: Character(x, y, maxHp)
	, currentMovementX(0)
	, currentMovementY(0)
	, directionX(0)
	, directionY(0)
	, movementInX(deltaX)
	, movementInY(deltaY)
	, damage(damage)
{
	// TODO: bools!
	if (movementInX != 0)
		directionX = 1;

	if (movementInY != 0)
		directionY = 1;
}


void Enemy::Draw()
{
	std::cout << cEnemySprite;
}

void Enemy::Update()
{
	if (movementInX != 0)
		UpdateDirection(currentMovementX, directionX, movementInX);
	if (movementInX != 0)
		UpdateDirection(currentMovementX, directionX, movementInX);

	this->SetPosition(pPosition->x + directionX, pPosition->y + directionY);
}

void Enemy::UpdateDirection(int& current, int& direction, int& movement)
{
	current += direction;

	if (std::abs(current) > movement)
	{
		current = movement * direction;
		direction *= -1;
	}
}
