#pragma once
#include "Room.h"
#include "GameEntity.h"
#include "Enums.h"

constexpr char cDoorSprite = (char)Sprite::DOOR;

class Door : public GameEntity
{
friend class GameEntity;
public:

	Door(int x, int y, Room* pRoom, Color closedColor);
	bool IsLocked() { return isLocked; }
	void Unlock() { isLocked = false; }
	void Draw() override;
	virtual Color GetColor() override;

	virtual bool CollideWith(GameEntity* collidedEntity) override;
	virtual std::string AsLegend() override { return " Door : " + std::string(1,cDoorSprite); }

private:
	Door() {};
	Room* nextRoom;
	// used to load file called <nextRoomFileName>.txt
	std::string nextRoomFileName;
	bool isLocked;
	Color openColor;
};

