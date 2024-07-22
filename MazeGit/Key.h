#pragma once
#include "GameEntity.h"
#include "Enums.h"

constexpr char keySprite = (char)Sprite::KEY;

class Key : public GameEntity
{
public:
	Key(int x, int y, Room* pRoom, Color color);

	virtual void Draw() override;

	virtual bool CollideWith(GameEntity* collidedEntity) override;
};

