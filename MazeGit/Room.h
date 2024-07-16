#pragma once
#include "Player.h"
#include "Enums.h"
#include "string"
#include <vector>

constexpr char cSpriteEmpty = (char)Sprite::EMPTY;
constexpr char cSpriteWall = (char)Sprite::WALL;

// TODO: room of varying sizes
class Room
{
	public:
		// Constructors
		Room();
		Room(int width, int height, char* pRoomData);
		~Room();

		bool Load(std::string filename, int* playerX, int* playerY);

		// Calls Draw on everything which is inside it
		void Draw();
		GameEntity* UpdateEntities(int x, int y);
		bool IsSpace(int x, int y);
		bool IsWall(int x, int y);
		bool Convert(int* playerX, int* playerY, char* pRoomBefore = nullptr);

	private:
		int width;
		int height;
		char* pRoomData;
		std::vector<GameEntity*> pEntities;

		int GetIndexFromXY(int x, int y);
		
		
};
