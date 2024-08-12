#pragma once
#include "GameEntity.h"

constexpr char cMoneySprite = (char)Sprite::MONEY;
class Money :
    public GameEntity
{
friend class GameEntity;
public:
    Money(int x, int y, Room* pRoom, int worth);

    int GetWorth() const { return worth; }
    void Draw() override;
    virtual bool CollideWith(GameEntity* collidedEntity) override;
    virtual std::string AsLegend() override { return "Money : " + std::string(1,cMoneySprite); }
private:
    Money();
    int worth;
};

