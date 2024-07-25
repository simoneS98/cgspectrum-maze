#include "Exit.h"
#include <iostream>
#include "Level.h"

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
	if(res == (char)Editor::EXIT)
		return "";

	return std::string(1,res);
}

bool Exit::CollideWith(GameEntity* collidedEntity)
{
	Player* player = dynamic_cast<Player*>(collidedEntity);

	// only Player Entities can change floors
	if(!player)
		return false;

	//Level::Load("test", "1");
}