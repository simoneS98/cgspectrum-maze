#pragma once
#include "Event.h"
class PlayerDeathEvent :
    public Event
{
public:
    PlayerDeathEvent();
    virtual bool Activate(Game* game = nullptr) override;
};



