#include "StartGameEvent.h"
#include "StateMachineExampleGame.h"

StartGameEvent::StartGameEvent(GameStateMachine* gsm)
    : m_pGsm(gsm)
{
}

bool StartGameEvent::Activate(Game* game)
{
    ((StateMachineExampleGame*)m_pGsm)->LoadScene(StateMachineExampleGame::SceneName::MAIN_MENU);
    //game->Load();
    return false;
}
