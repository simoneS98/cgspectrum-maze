#include "StartGameEvent.h"
#include "StateMachineExampleGame.h"
#include "LevelManager.h"

StartGameEvent::StartGameEvent(GameStateMachine* gsm)
    : m_pGsm(gsm)
{
}

bool StartGameEvent::Activate(Game* game)
{
    
    //game->Load();

    ((StateMachineExampleGame*)m_pGsm)->LoadScene(StateMachineExampleGame::SceneName::GAMEPLAY);
    //game->Load();
    isDone = true;
    return false;
}
