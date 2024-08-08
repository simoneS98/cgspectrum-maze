#pragma once
#include "Event.h"
class ShowLeaderboardEvent :
    public Event
{
public:
    ShowLeaderboardEvent();
    virtual void Activate(StateMachineExampleGame* gsm) override;
};

