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
	Player* player;
	Level level;
	bool isGameOver;
	bool userQuit;
	std::string levelName;
	std::string roomName;

public:
	Game(std::string levelName);
	~Game();

	bool Load(std::string roomName = "0", char *pRoomBefore = nullptr);
	void Run();

	bool IsGameOver();
	bool DidUserQuit() { return userQuit; }
	int GetPlayerHp() { return player->GetCurrentHp(); }
	int GetPlayerLives() { return player->GetLives(); }

private:
	void UpdatePlayerPosition(Point direction);
	bool UpdateGameWorld();
	void Draw();
	bool CheckIfGameEnded();
	bool PlayerCanMoveInDirection(Point direction);
	Point GetPlayerInput();

	bool HandleCollision(int newPlayerX, int newPlayerY);
	void LoadRoom(Room* room);

	void SetLevelName(std::string levelName) { this->levelName = levelName; }
};

