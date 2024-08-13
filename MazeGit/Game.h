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

	bool isGameOver;
	bool userQuit;
	std::string levelName;
	std::string roomName;

public:
	Game();
	Game(std::string levelName);
	~Game();

	bool Save();
	bool Load(std::string roomName = "0", char* pRoomBefore = nullptr);
	bool Load(Player*& pPlayer, std::string roomName = "0", char* pRoomBefore = nullptr);
	bool Resume();
	void Run();

	bool IsGameOver();
	bool DidUserQuit() { return userQuit; }
	void SaveScore();
	//int GetPlayerHp() { return player->GetCurrentHp(); }
	//int GetPlayerLives() { return player->GetLives(); }

private:
	void UpdatePlayerPosition(Point direction);
	bool UpdateGameWorld();
	void Draw();
	bool PlayerCanMoveInDirection(Point direction);
	Point GetPlayerInput();

	bool HandleCollision(int newPlayerX, int newPlayerY);
	void SetLevelName(std::string levelName) { this->levelName = levelName; }
	void DisplayAndSaveStats(
		std::string fileName,
		std::string playerName,
		int stepsTaken,
		int enemiesKilled,
		int livesLeft,
		int money
	);
};

