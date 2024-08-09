#include "PauseGameEvent.h"

PauseGameEvent::PauseGameEvent()
{
}

PauseGameEvent::~PauseGameEvent()
{
}

void PauseGameEvent::Activate(StateMachineExampleGame* gsm)
{
    gsm->PauseGame();
    isDone = true;
}
