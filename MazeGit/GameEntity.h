#pragma once
#include "Enums.h"
#include "Point.h"
class Room;
//#include "Key.h"

constexpr Color cDefaultColor = Color::DEFAULT;

class GameEntity
{
protected:
	Point* pPosition;
	bool isActive;
	Room* pRoom;
	Color color;
	EntityType type;
public:
	// Constructors
	// default parameter for color
	GameEntity(int x, int y, Room* pRoom, Color color = Color::DEFAULT);
	virtual ~GameEntity();

	int GetXPosition();
	int GetYPosition();
	int* GetXPositionPtr();
	int* GetYPositionPtr();
	
	Point GetPosition() { return *pPosition; }
	void SetPosition(int x, int y);

	//int GetColor() { return color; };
	void Remove() { isActive = false; }
	bool IsActive() { return isActive; }
	void Place(int x, int y);
	virtual Color GetColor() { return color; }



	// HAS to be overridden
	virtual void Draw() = 0;
	virtual bool TryUseKeyOn(GameEntity* lockedEntity) { return false; }
	virtual bool TryPickupKey(GameEntity* key) { return false; }

	virtual Point Update()
	{
		return Point(0,0);
	}

	virtual bool CollideWith(GameEntity* collidedEntity);

	EntityType GetType() { return type; }
};

