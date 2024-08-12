#pragma once
#include "Event.h"
class LoadLevelScoresEvent :
    public Event
{
private:
    std::string m_levelName;
public:
    LoadLevelScoresEvent(std::string levelName);
    // Inherited via Event
    void Activate(StateMachineExampleGame* gsm) override;
};

