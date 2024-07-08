#pragma once
#include "Player.h"
#include "Level.h"

class Game
{
	Player player;
	Level level;
	bool isGameOver;

public:
	Game();
	~Game();

	bool Load();
	void Run();

	bool IsGameOver();

private:
	bool Update();
	void Draw();
};

