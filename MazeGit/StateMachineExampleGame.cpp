#include "StateMachineExampleGame.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "ScoreMenuState.h"
#include "LevelManager.h"
#include "LevelScoresState.h"
#include "EventManager.h"
#include "ExitGameEvent.h"
#include "LoadLevelScoresEvent.h"
#include "GameplayMenuState.h"

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
    LoadScene(SceneName::MENU_MAIN);
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

void StateMachineExampleGame::ChooseLevel(std::string levelName)
{
    if (dynamic_cast<GameplayMenuState*>(m_pCurrentState))
    {
        LevelManager::GetInstance()->SetLevelName(levelName);
        //remove saves
        std::filesystem::remove("../levels/" + levelName + "/.tmp.room");
        std::filesystem::remove_all("../levels/" + levelName + "/saves");
        LoadScene(SceneName::GAMEPLAY, levelName.c_str());
    }
    else if (dynamic_cast<ScoreMenuState*>(m_pCurrentState))
        LoadScene(SceneName::SCORES, levelName.c_str());
}

void StateMachineExampleGame::LoadScene(SceneName scene)
{
    LoadScene(scene, nullptr);
}

void StateMachineExampleGame::LoadScene(SceneName scene, const char* levelName)
{
    switch (scene)
    {
    case SceneName::MENU_MAIN:
        m_pNextState = new MainMenuState(this);
        break;
    case SceneName::MENU_GAMEPLAY:
        m_pNextState = new GameplayMenuState(this);
        break;
    case SceneName::GAMEPLAY:
        m_pNextState = new GameplayState(this);
        break;
    case SceneName::MENU_SCORES:
        m_pNextState = new ScoreMenuState(this);
        break;
    case SceneName::SCORES:
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

void StateMachineExampleGame::ChangeRoom(std::string roomName)
{

    // clear tmp file
    std::filesystem::remove("../levels/" + LevelManager::GetInstance()->GetLevelName() + "/.tmp.room");
    m_pOwner->Save();
    m_pOwner->Load(roomName, LevelManager::GetInstance()->GetCurrentRoom()->GetName());
}

void StateMachineExampleGame::StartNewGame()
{
    if (dynamic_cast<MainMenuState*>(m_pCurrentState))
    {
        // clear game progress and saves
        LevelManager::GetInstance()->Clear();
        LoadScene(StateMachineExampleGame::SceneName::MENU_GAMEPLAY);
    }
}

// reference to player to assign it to the state calling this function
bool StateMachineExampleGame::ResumeGame()
{
    if (dynamic_cast<MainMenuState*>(m_pCurrentState)
        &&
        LevelManager::GetInstance()->GetCurrentRoom() != nullptr
        )
    {
        LoadScene(StateMachineExampleGame::SceneName::GAMEPLAY);
        return true;
    }

    return false;
}

void StateMachineExampleGame::InvalidatePlayerData(Player*& pPlayer)
{
    m_pOwner->SetPlayerData(pPlayer);
}
    
void StateMachineExampleGame::PauseGame()
{
    // Only works during gameplay
    // Should just move it to Quit()
    if (dynamic_cast<GameplayState*>(m_pCurrentState))
    {
        m_pOwner->Save(true);
        LoadScene(SceneName::MENU_MAIN);
    }

}

void StateMachineExampleGame::EndGame()
{
    m_pOwner->SaveScore();
}

void StateMachineExampleGame::ShowScores(const char* levelName)
{
    if (levelName == nullptr)
        LoadScene(SceneName::MENU_SCORES);
    else
        LoadScene(SceneName::SCORES, levelName);
}

void StateMachineExampleGame::Quit(std::string message)
{
    //if (dynamic_cast<GameplayState*>(m_pCurrentState))
    //    m_pOwner->Save();
    LevelManager::GetInstance()->Clear();
    system("cls");
    std::cout << message << std::endl;
    // wait seconds?
    
    // if on main menu, exit game
    if (dynamic_cast<MainMenuState*>(m_pCurrentState))
        exit(0);
    // else, go to main menu
    else if(dynamic_cast<LevelScoresState*>(m_pCurrentState))
        LoadScene(SceneName::MENU_SCORES);
    else
        LoadScene(SceneName::MENU_MAIN);
}
