#include "Exit.h"
#include <iostream>
#include "Level.h"
#include "EventManager.h"
#include "ChangeRoomEvent.h"
#include "ExitReachedEvent.h"

Exit::Exit(int x, int y, Room* pRoom, char nextRoomFileName)
	: GameEntity::GameEntity(x, y, pRoom)
	, nextRoomFileName(nextRoomFileName)
{
}

void Exit::Draw()
{
	std::cout << sprite;
}

std::string Exit::GetNextRoomAsString()
{
	char res = nextRoomFileName;
	/*if (res == (char)Editor::EXIT)
		return "";
	*/
	return std::string(1,res);
}

bool Exit::CollideWith(GameEntity* collidedEntity)
{
	Player* player = dynamic_cast<Player*>(collidedEntity);

	// only Player Entities can change floors
	if(!player)
		return false;

	//if(GetNextRoomAsString().empty())
	if (GetNextRoomAsString() == std::string() + (char)Editor::EXIT)
		EventManager::GetInstance()->Add(new ExitReachedEvent());
	else
		EventManager::GetInstance()->Add(new ChangeRoomEvent(GetNextRoomAsString()));

	return true;

	//Level::Load("test", "1");
}