#pragma once
#include "Event.h"
class ExitReachedEvent :
    public Event
{
public:
    ExitReachedEvent();
    virtual bool Activate(Game* game = nullptr) override;
};
