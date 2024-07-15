#include "Room.h"
#include <iostream>
#include <windows.h>  
#include <Constants.h>
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Exit.h"
#include "Enemy.h"
#include <assert.h>

Room::Room(int width, int height, char* pRoomData)
	: width(width)
	, height(height)
	, pRoomData(pRoomData)
{
	//this->pRoomData = pRoomData;
	Convert(0, 0);
}

Room::~Room()
{
	if (pRoomData != nullptr)
	{
		delete[] pRoomData;
		pRoomData = nullptr;
	}

	while (!pEntities.empty())
	{
		// deletes last element's pointer
		delete pEntities.back();
		// removes last element from vector
		pEntities.pop_back();
	}
}

void Room::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, cDefaultColor);

	// Draw the Room
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int indextToPrint = GetIndexFromXY(x,y);
			std::cout << pRoomData[indextToPrint];
		}
		std::cout << std::endl;
	}

	COORD entityCursorPosition;

	// Draw Entities
	/*
		front() access the first element
		back() access the last element
		end() returns an iterator to the end
		begin() returns an iterator to the beginning
	*/
	for (auto entity = pEntities.begin(); entity != pEntities.end(); ++entity)
	{
		if ((*entity)->IsActive())
		{
			entityCursorPosition.X = (*entity)->GetXPosition();
			entityCursorPosition.Y = (*entity)->GetYPosition();
			SetConsoleCursorPosition(console, entityCursorPosition);
			(*entity)->Draw();
		}
	}
}

bool Room::IsSpace(int x, int y)
{
	return pRoomData[GetIndexFromXY(x, y)] == cSpriteEmpty;
}

bool Room::IsWall(int x, int y)
{
	return pRoomData[GetIndexFromXY(x, y)] == cSpriteWall;
}

bool Room::Convert(int* playerX, int* playerY)
{
	bool anyWarnings = false;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = GetIndexFromXY(x, y);

			char tile = pRoomData[index];

			switch (tile)
			{
			case (char)Editor::CORNER:
			case (char)Editor::WALL_V:
			case (char)Editor::WALL_H:
				pRoomData[index] = cSpriteWall;
				break;
			case (char)Editor::KEY_GREEN:
				pRoomData[index] = cSpriteEmpty;
				pEntities.push_back(new Key(x, y, Color::GREEN));
				break;
			case (char)Editor::KEY_RED:
				pRoomData[index] = cSpriteEmpty;
				pEntities.push_back(new Key(x, y, Color::RED));
				break;
			case (char)Editor::KEY_BLUE:
				pRoomData[index] = cSpriteEmpty;
				pEntities.push_back(new Key(x, y, Color::BLUE));
				break;
			case (char)Editor::DOOR_RED:
				pRoomData[index] = cSpriteEmpty;
				pEntities.push_back(new Door(x, y, Color::RED));
				break;
			case (char)Editor::DOOR_GREEN:
				pRoomData[index] = cSpriteEmpty;
				pEntities.push_back(new Key(x, y, Color::GREEN));
				break;
			case (char)Editor::DOOR_BLUE:
				pRoomData[index] = cSpriteEmpty;
				pEntities.push_back(new Key(x, y, Color::BLUE));
				break;
			case (char)Editor::MONEY:
				pRoomData[index] = cSpriteEmpty;
				pEntities.push_back(new Money(x, y, 1 + rand() % 5));
				break;
			/*case (char)Editor::EXIT:
				pRoomData[index] = cSpriteEmpty;
				pEntities.push_back(new Exit(x, y,nullptr));
				break;
			*/
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				pEntities.push_back(new Exit( x, y, std::string(1,tile) ));
				break;
			case (char)Editor::PLAYER:
				pRoomData[index] = cSpriteEmpty;
				if (playerX != nullptr && playerY != nullptr)
				{
					*playerX = x;
					*playerY = y;
				}
				break;
			case (char)Editor::ENEMY:
				pEntities.push_back(new Enemy(x, y, 1+ rand() % 3));
				pRoomData[index] = cSpriteEmpty; // clear the level
				break;
			case (char)Editor::ENEMY_H:
				// delta x
				pEntities.push_back(new Enemy(x, y, 1 + rand() % 3, 3, 0));
				pRoomData[index] = cSpriteEmpty; // clear the level
				break;
			case (char)Editor::ENEMY_V:
				// delta y
				pEntities.push_back(new Enemy(x, y, 1 + rand() % 3, 0, 2));
				pRoomData[index] = cSpriteEmpty; // clear the level
				break;
			case (char)Editor::EMPTY:
				break;
			default:
				std::cout << "Invalid character in level file: " << pRoomData[index] << std::endl;
				anyWarnings = true;
				break;
			}


		}
	}

	return anyWarnings;
}

// Updates all entities and returns a colliding entity if there is one
GameEntity* Room::UpdateEntities(int x, int y)
{
	GameEntity* collidedEntity = nullptr;

	for (auto entity = pEntities.begin(); entity != pEntities.end(); ++entity)
	{
		(*entity)->Update(); // Update all entities

		if (x == (*entity)->GetXPosition() && y == (*entity)->GetYPosition())
		{
			// should only be able to collide with one actor
			assert(collidedEntity == nullptr);
			collidedEntity = (*entity);
		}
	}

	return collidedEntity;
}
int Room::GetIndexFromXY(int x, int y)
{
	return y * width + x;
}

/*
void HazardRoom::OnEnter(Player* p)
{
	p->TakeDamage(damage);
	__super::OnEnter(p);

}

HazardRoom::HazardRoom(Sprite type, int damage): Room(type)
{
	this->damage = damage;
}

HazardRoom::HazardRoom(Sprite type, Color color, int damage) : Room(type,color)
{
	this->damage = damage;
}

*/
