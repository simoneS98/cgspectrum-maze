#pragma once
#include "Event.h"
class ExitGameEvent :
    public Event
{
private:
    std::string m_message;
public:
    ExitGameEvent(const std::string exitCause = "");
    virtual void Activate(StateMachineExampleGame* gsm) override;
};

