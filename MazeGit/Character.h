#pragma once
#include "GameEntity.h"

class Character : GameEntity
{
	int hp;
	int maxHp;

public:
	virtual void MoveTo(int x, int y);
};

