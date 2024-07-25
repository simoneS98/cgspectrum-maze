#pragma once
#include "GameEntity.h"

constexpr char cWallSprite = (char)Sprite::WALL;

class Wall :
    public GameEntity
{
public:
    Wall(int x, int y, Room* pRoom);
    virtual void Draw() override;
    virtual bool CollideWith(GameEntity* collidedEntity) override;
};

