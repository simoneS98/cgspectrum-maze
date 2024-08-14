#pragma once
#include "Event.h"

class ResumeGameEvent :
    public Event
{
public:
    ResumeGameEvent();
    virtual void Activate(StateMachineExampleGame* game) override;
};

