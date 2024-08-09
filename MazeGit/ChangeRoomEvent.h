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
    virtual void Activate(StateMachineExampleGame* gsm) override;
};

