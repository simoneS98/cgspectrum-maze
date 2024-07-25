#pragma once
#include "Room.h"
#include "GameEntity.h"
#include "Enums.h"

constexpr char sprite = (char)Sprite::EXIT;

class Exit : public GameEntity
{
public:

	Exit(int x, int y, Room* pRoom, char nextRoomFileName);
	void Draw() override;
	std::string GetNextRoomAsString();
	bool CollideWith(GameEntity* collidedEntity) override;
private:
	//Room* nextRoom;
	// used to load file called <nextRoomFileName>.txt
	char nextRoomFileName;
};

