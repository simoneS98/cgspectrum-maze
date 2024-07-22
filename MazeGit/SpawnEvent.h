#pragma once
#include "Event.h"
#include "Key.h"
#include <functional>
#include "Room.h"
class SpawnEvent :
    public Event
{
private:
    Room* room;
    GameEntity* gameEntity;
    Point p;
public:
    SpawnEvent(Room* room, GameEntity* gameEntity, Point p);
    // Inherited via Event
    virtual bool Activate() override;



};

