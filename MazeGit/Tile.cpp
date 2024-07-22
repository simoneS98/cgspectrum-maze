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

void Tile::SetActive(GameEntity* gameEntity)
{
	delete activeEntity;
	activeEntity = gameEntity;
}

void Tile::SetPassive(GameEntity* gameEntity)
{
	delete passiveEntity;
	activeEntity = gameEntity;
}

void Tile::Draw()
{
	// active entity always has precedence
	if (activeEntity != nullptr)
		activeEntity->Draw();
	else if (activeEntity != nullptr)
		passiveEntity->Draw();
}
