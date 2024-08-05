#include "GameplayState.h"
#include "LevelManager.h"
#include "EventManager.h"

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
    , m_player(Player(nullptr))
    , m_level(Level())
    , m_beatGame(false)
{
}

void GameplayState::Enter()
{
    Load();
}

void GameplayState::Exit()
{
}

bool GameplayState::Update(bool processInput)
{
    LevelManager::GetInstance()->GetCurrentRoom()->UpdateEntities();
    // Generate Outputs
    //EventManager::GetInstance()->ActivateEvents(m_pOwner);
    return false;
}

void GameplayState::Draw()
{
}

bool GameplayState::Load()
{
    LevelManager::GetInstance()->Load("0");
    return false;
}
