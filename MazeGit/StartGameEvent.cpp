#include "StartGameEvent.h"
#include "StateMachineExampleGame.h"
#include "LevelManager.h"

StartGameEvent::StartGameEvent()
{
}

void StartGameEvent::Activate(StateMachineExampleGame* gsm)
{
    gsm->StartNewGame();
    isDone = true;
}
