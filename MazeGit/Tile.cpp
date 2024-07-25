#include "Tile.h"
#include <iostream>

Tile::Tile(GameEntity* activeEntity, GameEntity* passiveEntity)
	: activeEntity(activeEntity)
	, passiveEntity(passiveEntity)
{
}

void Tile::Add(GameEntity* gameEntity)
{
	if (gameEntity->GetType() == EntityType::ACTIVE)
		SetActive(gameEntity);
	else
		SetPassive(gameEntity);
}

void Tile::RemoveActive()
{
	//delete activeEntity;
	activeEntity = nullptr;
}

void Tile::RemovePassive()
{
	//delete passiveEntity;
	passiveEntity = nullptr;
}

void Tile::SetActive(GameEntity* gameEntity)
{
	//delete activeEntity;
	activeEntity = gameEntity;
}

void Tile::SetPassive(GameEntity* gameEntity)
{
	//delete passiveEntity;
	passiveEntity = gameEntity;
}

void Tile::Draw()
{
	// active entity always has precedence
	if (activeEntity != nullptr)
		activeEntity->Draw();
	else if (passiveEntity != nullptr)
		passiveEntity->Draw();
	else
		std::cout << " ";
}
