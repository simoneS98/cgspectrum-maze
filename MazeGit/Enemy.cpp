#include "Enemy.h"
#include <iostream>
#include "Player.h"
#include "AudioManager.h"

Enemy::Enemy(int x, int y, Room* pRoom, int maxHp, int damage, int deltaX, int deltaY)
	: Character(x, y, pRoom, maxHp)
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

Point Enemy::Update()
{
	if (movementInX != 0)
		UpdateDirection(currentMovementX, directionX, movementInX);
	if (movementInY != 0)
		UpdateDirection(currentMovementY, directionY, movementInY);
	
	//this->SetPosition(pPosition->x + directionX, pPosition->y + directionY);
	return Point(directionX, directionY);
}

bool Enemy::CollideWith(GameEntity* collidedEntity)
{
	//if(collidedEntity->
	// TODO: if collidedEntitis->IsFoe() ... why not?
	Player* foe = dynamic_cast<Player*>(collidedEntity);

	// can't be in a place occupied by something not considered foe
	if (foe)
	{
		AudioManager::GetInstance()->PlayPlayerDamagedSound();
		foe->TakeDamage(damage);
	}
		
	return false;
}


void Enemy::ChangeDirection()
{
	if (movementInX != 0)
		int _directionX = directionX * -1;
	if (movementInY != 0)
		int _directionY = directionY * -1;

	this->SetPosition(pPosition->x - directionX, pPosition->y - directionY);
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
