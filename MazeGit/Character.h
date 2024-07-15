#pragma once
#include "GameEntity.h"

class Character : public GameEntity
{
protected:
	int hp;
	int maxHp;

	virtual void Die();
public:
	Character(int x, int y, int maxHp);
	//virtual void MoveTo(int x, int y);
	int GetMaxHp();
	int GetCurrentHp();
	void TakeDamage(int amount);
};

