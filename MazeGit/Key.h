#pragma once
#include "GameEntity.h"
#include "Enums.h"

constexpr char keySprite = (char)Sprite::KEY;

class Key : public GameEntity
{
public:
	Key(int x, int y, Color color) : GameEntity(x,y,color) {}

	virtual void Draw() override;
};

