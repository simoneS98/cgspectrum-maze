#include "GameEntity.h"

GameEntity::GameEntity(int x, int y, Color color)
	: pPosition(new Point(x,y))
	, isActive(true)
	, color((int)color)
{
}

GameEntity::~GameEntity()
{
	delete pPosition;
	pPosition = nullptr;
}

int GameEntity::GetXPosition()
{
	return pPosition->x;
}

int GameEntity::GetYPosition()
{
	return pPosition->y;
}

int* GameEntity::GetXPositionPtr()
{
	return &(pPosition->x);
}

int* GameEntity::GetYPositionPtr()
{
	return &(pPosition->y);
}

void GameEntity::SetPosition(int x, int y)
{
	pPosition->x = x;
	pPosition->y = y;
}

void GameEntity::Place(int x, int y)
{
	pPosition->x = x;
	pPosition->y = y;
	isActive = true;
}

/*
bool GameEntity::TryPickupKey(int key)
{
	return false;
}

*/
bool GameEntity::HandleCollision(GameEntity* collidedEntity)
{
	return true;
}
