#include "Exit.h"
#include <iostream>

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
