#include "GameEntity.h"
#include <vector>

#pragma once
class Tile
{
private:
	// TODO: use std::vector<GameEntity*>
	//GameEntity* activeEntity;
	//GameEntity* passiveEntity;
	std::vector<GameEntity*> entities;
	//void SetActive(GameEntity* gameEntity);
	//void SetPassive(GameEntity* gameEntity);
public:
	//Tile();
	//Tile(GameEntity* activeEntity = nullptr, GameEntity* passiveEntity = nullptr);
	~Tile();
	Tile* Add(GameEntity* gameEntity);
	void Remove(GameEntity* gameEntity);
	GameEntity* GetFirstActive();
	GameEntity* GetFirst();
	void RefreshActivations();
	std::string GetC() {
		if (entities.empty()) { return " "; }
		else { return "qualcosa"; }
	};
	//void RemoveActive();
	//void RemovePassive();


	//GameEntity* GetActive() { return activeEntity; }
	//GameEntity* GetPassive() { return passiveEntity; }
	void Draw();

	//bool HandleCollision(Tile otherTile);
	//bool IsEmpty() { return activeEntity == nullptr && passiveEntity == nullptr; }
	bool IsEmpty() { return entities.empty(); }

};

