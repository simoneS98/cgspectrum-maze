#pragma once
class GameEntity
{
	int x;
	int y;
public:

	// Constructors
	GameEntity(int x, int y);

	virtual void Draw();
};

