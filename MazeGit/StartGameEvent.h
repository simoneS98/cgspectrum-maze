#pragma once
#include "Event.h"
#include "GameStateMachine.h"

class StartGameEvent :
    public Event
{
private:
    GameStateMachine* m_pGsm;
public:
    StartGameEvent(GameStateMachine* gsm);
    virtual bool Activate(Game* game) override;
};

