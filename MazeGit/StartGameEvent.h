#pragma once
#include "Event.h"

class StartGameEvent :
    public Event
{
public:
    StartGameEvent();
    virtual void Activate(StateMachineExampleGame* game) override;
};

