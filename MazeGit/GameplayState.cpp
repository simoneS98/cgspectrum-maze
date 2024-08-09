#include "GameplayState.h"
#include "LevelManager.h"
#include "EventManager.h"

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
    //, m_pPlayer(new Player(nullptr))
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
    LevelManager::GetInstance()->GetCurrentRoom()->Draw();
    m_pPlayer->DisplayInfo();
}

bool GameplayState::Load()
{
    if (LevelManager::GetInstance()->GetCurrentRoom() == nullptr)
    {
        std::cout << "Which level do you want to play? (TODO: print list of levels)";
        std::string levelName;
        std::cin >> levelName;
        LevelManager::GetInstance()->SetLevelName(levelName);
    }
    
    m_pOwner->LoadGame(m_pPlayer);
    //LevelManager::GetInstance()->Load("0");
    return false;
}
