#pragma once
#include "Character.h"

constexpr char cEnemySprite = (char)Sprite::ENEMY;
// TODO: random direction every time it touches a wall
class Enemy :
    public Character
{
friend class GameEntity;

public:
    Enemy(int x, int y, Room* pRoom, int maxHp, int damage = 0, int deltaX = 0, int deltaY = 0);

    virtual void Draw() override;
    virtual Point Update() override;
    virtual bool CollideWith(GameEntity* collidedEntity) override;

    void ChangeDirection();

    int GetDamage() { return damage; }
    virtual std::string AsLegend() override { return "Enemy : " + std::string(1,cEnemySprite); }

private:
    Enemy();
    // how many tiles the Enemy moves before switching direction
    int movementInX;
    int movementInY;
    
    // currentMovement tracks the position
    int currentMovementX;
    int currentMovementY;

    // TODO: switch to bool? bool facingLeft, bool facingUp
    // direction determines how much the currentMovement increases/decreases
    // (if next tile will be in front of or behind the Enemy)
    int directionX;
    int directionY;

    int damage;

    void UpdateDirection(int& current, int& direction, int& movement);

    Point GetDirection() { return Point(directionX, directionY); }
};

