#pragma once
#include "Player.h"
#include "Level.h"

constexpr char cArrowInput = (char)Input::ARROW_IN;
constexpr char cArrowLeft = (char)Input::ARROW_LEFT;
constexpr char cArrowRight = (char)Input::ARROW_RIGHT;
constexpr char cArrowDown = (char)Input::ARROW_DOWN;
constexpr char cArrowUp = (char)Input::ARROW_UP;
constexpr char cEscape = (char)Input::ESC;

class Game
{
	Player player;
	Level level;
	bool isGameOver;
	bool userQuit;

public:
	Game();
	~Game();

	bool Load(std::string levelName);
	void Run();

	bool IsGameOver();
	bool DidUserQuit() { return userQuit; }
	int GetPlayerHp() { return player.GetCurrentHp(); }
	int GetPlayerLives() { return player.GetLives(); }

private:
	bool Update();
	void Draw();

	bool HandleCollision(int newPlayerX, int newPlayerY);
	void LoadRoom(Room* room);
};

