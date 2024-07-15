#pragma once
#include "Room.h"
#include "GameEntity.h"
#include "Enums.h"

constexpr char sprite = (char)Sprite::EXIT;

class Exit : public GameEntity
{
public:

	Exit(int x, int y, std::string fileName);
	void Draw() override;
	Room* GetNextRoom() { return nextRoom; }
private:
	Room* nextRoom;
	// used to load file called <nextRoomFileName>.txt
	std::string nextRoomFileName;
};

