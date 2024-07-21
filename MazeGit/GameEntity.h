#pragma once
#include "Enums.h"
#include "Point.h"
//#include "Key.h"

constexpr int cDefaultColor = (int)Color::DEFAULT;

class GameEntity
{
protected:
	Point* pPosition;
	bool isActive;
	int color;

public:
	// Constructors
	// default parameter for color
	GameEntity(int x, int y, Color color = Color::DEFAULT);
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
	virtual Color GetColor() { return Color(color); }



	// HAS to be overridden
	virtual void Draw() = 0;
	virtual bool TryUseKeyOn(GameEntity* lockedEntity) { return false; }
	virtual bool TryPickupKey(GameEntity* key) { return false; }

	virtual Point Update()
	{
		return Point(0,0);
	}

	virtual bool HandleCollision(GameEntity* collidedEntity);
};

