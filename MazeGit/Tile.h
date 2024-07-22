#include "GameEntity.h"

#pragma once
class Tile
{
private:
	GameEntity* activeEntity;
	GameEntity* passiveEntity;
public:
	Tile(GameEntity* activeEntity = nullptr, GameEntity* passiveEntity = nullptr);
	void Add(GameEntity* gameEntity);
	void SetActive(GameEntity* gameEntity);
	void SetPassive(GameEntity* gameEntity);

	GameEntity* GetActive() { return activeEntity; }
	GameEntity* GetPassive() { return passiveEntity; }
	void Draw();

	bool IsEmpty() { return activeEntity == nullptr && passiveEntity == nullptr; }
};

