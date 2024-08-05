#include "StateMachineExampleGame.h"
#include "MainMenuState.h";
#include "GameplayState.h";

StateMachineExampleGame::StateMachineExampleGame(Game* pOwner)
    : m_pOwner(pOwner)
    , m_pCurrentState(nullptr)
    , m_pNextState(nullptr)
{
}

bool StateMachineExampleGame::Init()
{
    // default scene
    LoadScene(SceneName::MAIN_MENU);
    return true;
}

bool StateMachineExampleGame::UpdateCurrentState(bool processInput)
{
    bool done = false;
    if (m_pNextState != nullptr)
    {
        ChangeState(m_pNextState);
        m_pNextState = nullptr;
    }

    if (m_pCurrentState != nullptr)
        done = m_pCurrentState->Update(processInput);

    return done;
}

bool StateMachineExampleGame::DrawCurrentState()
{
    if (m_pCurrentState)
        m_pCurrentState->Draw();
    return false;
}

void StateMachineExampleGame::ChangeState(GameState* pNextState)
{
    if (m_pCurrentState)
        m_pCurrentState->Exit();

    delete m_pCurrentState;

    m_pCurrentState = pNextState;
    m_pCurrentState->Enter();
}

bool StateMachineExampleGame::Cleanup()
{
    if (m_pCurrentState)
    {
        m_pCurrentState->Exit();
        delete m_pCurrentState;
    }
    return true;
}

void StateMachineExampleGame::LoadScene(SceneName scene)
{
    switch (scene)
    {
    case SceneName::MAIN_MENU:
        m_pNextState = new MainMenuState(this);
        break;
    case SceneName::GAMEPLAY:
        m_pNextState = new GameplayState(this);
        break;
    default:
        break;
    }
}
    
        
