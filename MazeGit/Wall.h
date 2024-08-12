#pragma once
#include "GameEntity.h"

constexpr char cWallSprite = (char)Sprite::WALL;

class Wall :
    public GameEntity
{
friend class GameEntity;

public:
    Wall(int x, int y, Room* pRoom);
    virtual void Draw() override;
    virtual bool CollideWith(GameEntity* collidedEntity) override;
    virtual std::string AsLegend() override { return "Wall : " + std::string(1,cWallSprite); }
private:
    Wall() {};
};