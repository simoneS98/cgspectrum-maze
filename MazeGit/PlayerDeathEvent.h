#pragma once
#include "Event.h"
class PlayerDeathEvent :
    public Event
{
public:
    PlayerDeathEvent();
    virtual void Activate(StateMachineExampleGame* gsm) override;
};



