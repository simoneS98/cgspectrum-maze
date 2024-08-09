#pragma once
#include "Event.h"

class PauseGameEvent :
    public Event
{
public:
    PauseGameEvent();
    ~PauseGameEvent();
    virtual void Activate(StateMachineExampleGame* gsm);
};

