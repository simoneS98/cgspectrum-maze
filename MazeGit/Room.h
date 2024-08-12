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
		Room(int width, int height, char* pRoomData, std::string name);
		~Room();

		bool Save();
		bool Load(std::string filename, int* playerX, int* playerY);
		char* GetName() { return &name[0]; }

		// Calls Draw on everything which is inside it
		void Draw();
		GameEntity* UpdateEntities();
		bool IsSpace(int x, int y);
		bool IsWall(int x, int y);
		bool IsWall(int index);
		bool Convert(Player* player, char pRoomBefore);
		char* RevertToCharMap();
		bool PlaceAt(GameEntity* gameEntity, Point p);
		void RemoveFrom(GameEntity* gameEntity, Point p);
		void MoveEntity(Point startPos, Point endPos);
		bool operator==(const Room* otherRoom);
		int GetWidth() { return width; }

	private:
		int width;
		int height;
		char* pRoomData;
		std::string name;
		// well of course Dictionaries will be better for this...
		//GameEntity** pRoomEntities;
		std::vector<Tile*> pRoomEntities;
		//std::vector<GameEntity*> pEntities;

		void UpdateEntity(GameEntity* entity);
		int GetIndexFromXY(int x, int y);

		// use CollisionManager?
		bool HandleCollision(GameEntity* g1, GameEntity* g2);
		bool HandleCollision(GameEntity* g1, Tile* destinationTile);
		
		
};
