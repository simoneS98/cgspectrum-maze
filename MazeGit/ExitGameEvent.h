#pragma once
#include "Event.h"
class ExitGameEvent :
    public Event
{
public:
    ExitGameEvent();
    virtual bool Activate() override;
};

