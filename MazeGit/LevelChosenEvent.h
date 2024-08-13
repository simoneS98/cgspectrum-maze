#pragma once
#include "Event.h"
class LevelChosenEvent :
    public Event
{
private:
    std::string m_levelName;
public:
    LevelChosenEvent(std::string levelName);
    // Inherited via Event
    virtual void Activate(StateMachineExampleGame* gsm) override;
};

