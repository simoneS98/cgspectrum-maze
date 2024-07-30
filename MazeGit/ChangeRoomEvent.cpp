#include "ChangeRoomEvent.h"
#include "LevelManager.h"
ChangeRoomEvent::ChangeRoomEvent(std::string nextRoom)
    : Event()
    , nextRoom(nextRoom)
{

}
bool ChangeRoomEvent::Activate(Game* game)
{
    game->Load(nextRoom, LevelManager::GetInstance()->GetCurrentRoom()->GetName());
    isDone = true;
    //LevelManager::GetInstance()->Load(nextRoom);
    return true;
}
