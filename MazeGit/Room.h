#pragma once
#include "Player.h"
#include "Enums.h"
#include "string"
#include <vector>
#include "Tile.h"

constexpr char cSpriteEmpty = (char)Sprite::EMPTY;
constexpr char cSpriteWall = (char)Sprite::WALL;

// TODO: room of varying sizes
class Room
{
	public:
		// Constructors
		Room(int width, int height, char* pRoomData);
		~Room();

		bool Load(std::string filename, int* playerX, int* playerY);

		// Calls Draw on everything which is inside it
		void Draw();
		GameEntity* UpdateEntities();
		bool IsSpace(int x, int y);
		bool IsWall(int x, int y);
		bool IsWall(int index);
		bool Convert(Player* player, char* pRoomBefore = nullptr);
		bool PlaceAt(GameEntity* gameEntity, Point p);
		void RemoveFrom(GameEntity* gameEntity, Point p);
		void MoveEntity(Point startPos, Point endPos);

	private:
		int width;
		int height;
		char* pRoomData;
		// well of course Dictionaries will be better for this...
		//GameEntity** pRoomEntities;
		std::vector<Tile*> pRoomEntities;
		std::vector<GameEntity*> pEntities;

		int GetIndexFromXY(int x, int y);

		// use CollisionManager?
		bool HandleCollision(GameEntity* g1, GameEntity* g2);
		bool HandleCollision(GameEntity* g1, Tile* destinationTile);
		
		
};
