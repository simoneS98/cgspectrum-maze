#pragma once
#include "Event.h"
class ChangeRoomEvent :
    public Event
{
private:
    std::string nextRoom;
public:
    ChangeRoomEvent(std::string nextRoom);
    // Inherited via Event
    virtual bool Activate(Game* game) override;
};

