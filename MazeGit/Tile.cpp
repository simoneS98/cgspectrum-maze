#include "Tile.h"
#include <iostream>

/*
Tile::Tile(GameEntity* activeEntity, GameEntity* passiveEntity)
	: activeEntity(activeEntity)
	, passiveEntity(passiveEntity)
{
}
*/


Tile* Tile::Add(GameEntity* gameEntity)
{
	entities.push_back(gameEntity);
	/*
	if (gameEntity->GetType() == EntityType::ACTIVE)
		SetActive(gameEntity);
	else
		SetPassive(gameEntity);
	*/
	return this;
}

void Tile::Remove(GameEntity* gameEntity)
{
	for (auto entity = entities.begin() ; entity != entities.end() ; ++entity)
	{
		if (gameEntity == (*entity))
		{ 
			entities.erase(entity);
			return;
		}
	}
}

GameEntity* Tile::GetFirstActive()
{
	for (auto entity = entities.begin(); entity != entities.end(); ++entity)
	{
		if ((*entity)->CanActivate())
		{
			return *entity;
		}
	}

	return nullptr;
}

GameEntity* Tile::GetFirst()
{
	return entities[0];
}

void Tile::RefreshActivations()
{
	for (auto entity = entities.begin(); entity != entities.end(); ++entity)
	{
		(*entity)->RefreshActivation();
	}
}

/*
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
*/
void Tile::Draw()
{
	entities.back()->Draw();
	/*
	// active entity always has precedence
	if (activeEntity != nullptr)
		activeEntity->Draw();
	else if (passiveEntity != nullptr)
		passiveEntity->Draw();
	else
		std::cout << " ";
	*/
}
