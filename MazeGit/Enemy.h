#pragma once
#include "Character.h"

constexpr char cEnemySprite = (char)Sprite::ENEMY;
class Enemy :
    public Character
{
public:
    Enemy(int x, int y, int maxHp, int deltaX = 0, int deltaY = 0, int damage = 0);

    virtual void Draw() override;
    virtual void Update() override;

    int GetDamage() { return damage; }
private:
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
};

