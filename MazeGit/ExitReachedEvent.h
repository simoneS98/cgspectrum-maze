#pragma once
#include "Event.h"
class ExitReachedEvent :
    public Event
{
public:
    ExitReachedEvent();
    virtual void Activate(StateMachineExampleGame* gsm) override;
};
