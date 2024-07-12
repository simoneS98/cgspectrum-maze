#pragma once
#include "Room.h"
#include "GameEntity.h"
#include "Enums.h"

constexpr char sprite = (char)RoomContent::DOOR;

class Door : GameEntity
{
	Room* nextRoom;
	// used to load file called <nextRoomFileName>.txt
	std::string nextRoomFileName;
	bool isLocked;

public:

	Door(int x, int y, std::string fileName);
	void Unlock();
	void Draw() override;
};

