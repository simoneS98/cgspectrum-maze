#include "ChangeRoomEvent.h"
#include "LevelManager.h"
ChangeRoomEvent::ChangeRoomEvent(std::string nextRoom)
    : Event()
    , nextRoom(nextRoom)
{

}
void ChangeRoomEvent::Activate(StateMachineExampleGame* gsm)
{
    gsm->ChangeRoom(nextRoom, LevelManager::GetInstance()->GetCurrentRoom()->GetName());
    isDone = true;
}
