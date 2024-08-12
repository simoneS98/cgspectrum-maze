#include "StateMachineExampleGame.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "ScoreMenuState.h"
#include "LevelManager.h"
#include "LevelScoresState.h"
#include "EventManager.h"
#include "ExitGameEvent.h"
#include "LoadLevelScoresEvent.h"

StateMachineExampleGame* StateMachineExampleGame::instance  = nullptr;

StateMachineExampleGame::StateMachineExampleGame()
    : m_pCurrentState(nullptr)
    , m_pNextState(nullptr)
{
}

bool StateMachineExampleGame::Init(Game* pOwner)
{
    m_pOwner = pOwner;
    // default scene
    LoadScene(SceneName::MAIN_MENU);
    return true;
}

bool StateMachineExampleGame::UpdateCurrentState(bool processInput)
{
    bool done = false;

    DrawCurrentState();

    EventManager::GetInstance()->ActivateEvents(this);

    if (m_pNextState != nullptr)
    {
        ChangeState(m_pNextState);
        m_pNextState = nullptr;
    }

    if (m_pCurrentState != nullptr)
    {
        done = m_pCurrentState->Update(processInput);
    }
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
    case SceneName::SCORE_MENU:
        m_pNextState = new ScoreMenuState(this);
        break;
    case SceneName::SCORE_LEVEL_DETAIL:
        //if(dynamic_cast<ScoreMenuState*>(m_pCurrentState))
        //    m_pNextState = new LevelScoresState(m_pCurrentState);
        break;
    default:
        break;
    }
}

void StateMachineExampleGame::LoadScene(SceneName scene, const char* levelName)
{
    switch (scene)
    {
    case SceneName::MAIN_MENU:
        m_pNextState = new MainMenuState(this);
        break;
    case SceneName::GAMEPLAY:
        m_pNextState = new GameplayState(this);
        break;
    case SceneName::SCORE_MENU:
        m_pNextState = new ScoreMenuState(this);
        break;
    case SceneName::SCORE_LEVEL_DETAIL:
        m_pNextState = new LevelScoresState(this,levelName);
        break;
    default:
        break;
    }
}
bool StateMachineExampleGame::LoadGame(Player*& pPlayer)
{
    return m_pOwner->Load(pPlayer);
}

void StateMachineExampleGame::ChangeRoom(std::string roomName, std::string levelName)
{
    m_pOwner->Save();
    m_pOwner->Load(roomName, LevelManager::GetInstance()->GetCurrentRoom()->GetName()/*&levelName[0]*/);
}

void StateMachineExampleGame::StartNewGame()
{
    if (dynamic_cast<MainMenuState*>(m_pCurrentState))
        LoadScene(StateMachineExampleGame::SceneName::GAMEPLAY);
}
    
void StateMachineExampleGame::PauseGame()
{
    // Only works during gameplay
    if (dynamic_cast<GameplayState*>(m_pCurrentState))
        LoadScene(SceneName::MAIN_MENU);

}

void StateMachineExampleGame::EndGame()
{
    m_pOwner->SaveScore();
}

void StateMachineExampleGame::ShowScores(const char* levelName)
{
    if (levelName == nullptr)
        LoadScene(SceneName::SCORE_MENU);
    else
        LoadScene(SceneName::SCORE_LEVEL_DETAIL, levelName);
}

void StateMachineExampleGame::Quit(std::string message)
{
    system("cls");
    std::cout << message << std::endl;
    // wait seconds?
    
    // if on main menu, exit game
    if (dynamic_cast<MainMenuState*>(m_pCurrentState))
        exit(0);
    // else, go to main menu
    else if(dynamic_cast<LevelScoresState*>(m_pCurrentState))
        LoadScene(SceneName::SCORE_MENU);
    else
        LoadScene(SceneName::MAIN_MENU);
}
