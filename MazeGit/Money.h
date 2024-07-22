#pragma once
#include "GameEntity.h"

constexpr char cMoneySprite = (char)Sprite::MONEY;
class Money :
    public GameEntity
{
public:
    Money(int x, int y, Room* pRoom, int worth);

    int GetWorth() const { return worth; }
    void Draw() override;
private:
    int worth;
};

