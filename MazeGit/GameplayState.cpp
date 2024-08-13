#include "GameplayState.h"
#include "LevelManager.h"
#include "EventManager.h"
#include <thread>
#include "Wall.h"
#include "Enemy.h"
#include "Door.h"
#include "Money.h"
#include <filesystem>
#include "LevelChosenEvent.h"

using Option = Options::MenuOption;

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
    : m_pOwner(pOwner)
    //, m_pPlayer(new Player(nullptr))
    , m_level(Level())
    , m_beatGame(false)
{
}

void GameplayState::Enter()
{
    // check if should resume or start new game
    if (LevelManager::GetInstance()->GetCurrentRoom() == nullptr)
    {
        Load();
    }
    else
        Resume();

    Draw();
}

void GameplayState::Exit()
{
}

bool GameplayState::Update(bool processInput)
{
    LevelManager::GetInstance()->GetCurrentRoom()->UpdateEntities();
    return false;
}

void GameplayState::Draw()
{
    LevelManager::GetInstance()->GetCurrentRoom()->Draw();
    m_pPlayer->DisplayInfo();
    std::cout << std::endl;
    ShowLegend();
}

bool GameplayState::Load()
{
    
    if (LevelManager::GetInstance()->GetCurrentRoom() != nullptr)
    {
        //throw error
        return false;
    }
   
    return m_pOwner->LoadGame(m_pPlayer);

}

bool GameplayState::Resume()
{
    Room* room = LevelManager::GetInstance()->GetCurrentRoom();

    if (LevelManager::GetInstance()->GetCurrentRoom() == nullptr)
    {
        //throw error
        return false;
    }

    //LevelManager::GetInstance()->LoadSave();

    return false;
}

const void GameplayState::ShowLegend()
{
    std::string border = std::string(1,(char)Sprite::PERIMETER);
    Wall wall = GameEntity::Fake<Wall>();
    Enemy enemy = GameEntity::Fake<Enemy>();
    Door door = GameEntity::Fake<Door>();
    Key key = GameEntity::Fake<Key>();
    Money money = GameEntity::Fake<Money>();

    std::string legend =
        border +
        " " + wall.AsLegend() + " " +
        border +
        " " + enemy.AsLegend() + " " +
        border +
        " " + door.AsLegend() + " " +
        border +
        " " + key.AsLegend() + " " +
        border +
        " " + money.AsLegend() + " " +
        border;

    int width = legend.size();

    for (int i = 0; i < width; i++)
        std::cout << border;
    
    std::cout << std::endl << legend << std::endl;

    for (int i = 0; i < width; i++)
        std::cout << border;
}
