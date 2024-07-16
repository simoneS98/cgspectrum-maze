#include "Exit.h"
#include <iostream>

Exit::Exit(int x, int y, char nextRoomFileName) : GameEntity::GameEntity(x, y)
{
	this->nextRoomFileName = nextRoomFileName;
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
