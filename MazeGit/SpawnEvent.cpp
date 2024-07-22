#include "SpawnEvent.h"

SpawnEvent::SpawnEvent(Room* room, GameEntity* gameEntity, Point p)
    : Event()
    , room(room)
    , gameEntity(gameEntity)
    , p(p)
{
}

bool SpawnEvent::Activate()
{
    return false;
}