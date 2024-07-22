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
		GameEntity* UpdateEntities();
		bool IsSpace(int x, int y);
		bool IsWall(int x, int y);
		bool Convert(Player* player, char* pRoomBefore = nullptr);
		bool PlaceAt(GameEntity* gameEntity, Point p);

	private:
		int width;
		int height;
		char* pRoomData;
		// well of course Dictionaries will be better for this...
		//GameEntity** pRoomEntities;
		std::vector<GameEntity*> pRoomEntities;
		std::vector<GameEntity*> pEntities;

		int GetIndexFromXY(int x, int y);
		
		
		
};
