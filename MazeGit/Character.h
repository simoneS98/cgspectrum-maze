#pragma once
#include "GameEntity.h"
#include "Key.h"

class Character : public GameEntity
{
protected:
	int hp;
	int maxHp;
	Key* pCurrentKey;

	virtual void Die();
public:
	Character(int x, int y, Room* pRoom, int maxHp);
	//virtual void MoveTo(int x, int y);
	int GetMaxHp();
	int GetCurrentHp();
	virtual void TakeDamage(int amount);
	virtual bool TryPickupKey(GameEntity* key) override;
	virtual std::string AsLegend() = 0;
};

