#include "ResumeGameEvent.h"
#include "StateMachineExampleGame.h"
#include "LevelManager.h"

ResumeGameEvent::ResumeGameEvent()
{
}

void ResumeGameEvent::Activate(StateMachineExampleGame* gsm)
{
    gsm->ResumeGame();
    isDone = true;
}
