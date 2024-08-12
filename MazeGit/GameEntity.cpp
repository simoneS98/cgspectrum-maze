#include "GameEntity.h"
#include "Room.h"
#include "LevelManager.h"

GameEntity::GameEntity()
	: pPosition(nullptr)
	, pRoom(nullptr)
	, isActive(false)
	, color(Color::DEFAULT)
	, canActivate(false)
{
}

GameEntity::GameEntity(int x, int y, Room* pRoom, Color color)
	: pPosition(new Point(x,y))
	, pRoom(pRoom)
	, isActive(true)
	, color(color)
	, canActivate(true)
{
}

GameEntity::~GameEntity()
{
	delete pPosition;
	pPosition = nullptr;
	//delete pRoom;

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
	pRoom->PlaceAt(this, Point(x, y));
	//pPosition->x = x;
	//pPosition->y = y;
	isActive = true;
}

/*
bool GameEntity::TryPickupKey(int key)
{
	return false;
}

*/
bool GameEntity::CollideWith(GameEntity* collidedEntity)
{
	return true;
}
