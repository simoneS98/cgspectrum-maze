#include "Wall.h"
#include <iostream>
#include "AudioManager.h"

Wall::Wall(int x, int y, Room* pRoom)
    : GameEntity(x,y,pRoom)
{
    type = EntityType::ACTIVE;
}

void Wall::Draw()
{
    std::cout << cWallSprite;
}

bool Wall::CollideWith(GameEntity* collidedEntity)
{
    // nothing can go through a wall...for now
    AudioManager::GetInstance()->PlayPathBlockedSound();
    return false;
}
