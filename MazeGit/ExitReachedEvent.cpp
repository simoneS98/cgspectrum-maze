#include "ExitReachedEvent.h"

ExitReachedEvent::ExitReachedEvent()
{
}

void ExitReachedEvent::Activate(StateMachineExampleGame* gsm)
{
    gsm->EndGame();
    isDone = true;
}
