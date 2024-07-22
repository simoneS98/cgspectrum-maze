#pragma once
#include "Event.h"
class PlayerDeathEvent :
    public Event
{
public:
    PlayerDeathEvent();
    virtual bool Activate() override;
};



