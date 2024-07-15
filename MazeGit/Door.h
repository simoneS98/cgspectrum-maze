#pragma once
#include "Room.h"
#include "GameEntity.h"
#include "Enums.h"

constexpr char cDoorSprite = (char)Sprite::DOOR;

class Door : public GameEntity
{
public:

	Door(int x, int y, Color closedColor, Color openColor = Color::DEFAULT);
	bool IsLocked() { return isLocked; }
	void Unlock() { isLocked = false; }
	void Draw() override;

private:
	Room* nextRoom;
	// used to load file called <nextRoomFileName>.txt
	std::string nextRoomFileName;
	bool isLocked;
	int closedColor;
};

