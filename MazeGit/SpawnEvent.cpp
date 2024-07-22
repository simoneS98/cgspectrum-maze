#include "SpawnEvent.h"

bool SpawnEvent::Activate()
{
    return false;
}

SpawnEvent::SpawnEvent(Room* room, GameEntity* gameEntity, int x, int y)
    : Event()
{
}
