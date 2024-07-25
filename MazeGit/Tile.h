#include "GameEntity.h"

#pragma once
class Tile
{
private:
	// TODO: use std::vector<GameEntity*>
	GameEntity* activeEntity;
	GameEntity* passiveEntity;
	void SetActive(GameEntity* gameEntity);
	void SetPassive(GameEntity* gameEntity);
public:
	Tile(GameEntity* activeEntity = nullptr, GameEntity* passiveEntity = nullptr);
	void Add(GameEntity* gameEntity);
	void RemoveActive();
	void RemovePassive();


	GameEntity* GetActive() { return activeEntity; }
	GameEntity* GetPassive() { return passiveEntity; }
	void Draw();

	//bool HandleCollision(Tile otherTile);
	bool IsEmpty() { return activeEntity == nullptr && passiveEntity == nullptr; }
};

