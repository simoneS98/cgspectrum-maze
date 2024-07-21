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
	//pRoomEntities = new GameEntity*[width * height];
	pRoomEntities = std::vector<GameEntity*>(width * height, nullptr);
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
	//TODO: what about the  player???
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, cDefaultColor);

	// Draw the Room
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int indexToPrint = GetIndexFromXY(x,y);

			GameEntity* e = pRoomEntities[indexToPrint];

			if (e != nullptr)
			{
				e->Draw();
			//	delete e;
				//e = nullptr;
			}
			else
			{
				// of course is it better to use walls as gameentities...
				// ...and leave empty spaces as nullptrs
				std::cout << pRoomData[indexToPrint];
			}
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

	SetConsoleCursorPosition(console, COORD{ 0,cMaxRoomHeight });
}

bool Room::IsSpace(int x, int y)
{
	return pRoomData[GetIndexFromXY(x, y)] == cSpriteEmpty;
}

bool Room::IsWall(int x, int y)
{
	return pRoomData[GetIndexFromXY(x, y)] == cSpriteWall;
}

// TODO: move to Utils class?
bool Room::Convert(Player *player, char* pRoomNameBefore)
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
				pRoomEntities[index] = new Key(x, y, Color::GREEN);
				//pEntities.push_back(new Key(x, y, Color::GREEN));
				break;
			case (char)Editor::KEY_RED:
				pRoomData[index] = cSpriteEmpty;
				pRoomEntities[index] = new Key(x, y, Color::RED);
				//pEntities.push_back(new Key(x, y, Color::RED));
				break;
			case (char)Editor::KEY_BLUE:
				pRoomData[index] = cSpriteEmpty;
				pRoomEntities[index] = new Key(x, y, Color::BLUE);
				//pEntities.push_back(new Key(x, y, Color::BLUE));
				break;
			case (char)Editor::DOOR_RED:
				pRoomData[index] = cSpriteEmpty;
				pRoomEntities[index] = new Door(x, y, Color::RED);
				//pEntities.push_back(new Door(x, y, Color::RED));
				break;
			case (char)Editor::DOOR_GREEN:
				pRoomData[index] = cSpriteEmpty;
				pRoomEntities[index] = new Door(x, y, Color::GREEN);
				//pEntities.push_back(new Door(x, y, Color::GREEN));
				break;
			case (char)Editor::DOOR_BLUE:
				pRoomData[index] = cSpriteEmpty;
				pRoomEntities[index] = new Door(x, y, Color::BLUE);
				//pEntities.push_back(new Door(x, y, Color::BLUE));
				break;
			case (char)Editor::MONEY:
				pRoomData[index] = cSpriteEmpty;
				pRoomEntities[index] = new Money(x, y, 1 + rand() % 5);
				//pEntities.push_back(new Money(x, y, 1 + rand() % 5));
				break;
			case (char)Editor::EXIT:
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
				// if player is coming from another floor, change his coordinates to the relative door
				// won't work if there is more than one door with same char in a floor
				/*if (pRoomNameBefore != nullptr)
				{
					if (*pRoomNameBefore == tile)
					{
						*playerX = x;
						*playerY = y;
					}

				}*/
				pRoomEntities[index] = new Exit(x, y, tile);
				//pEntities.push_back(new Exit( x, y, tile));
				break;
			case (char)Editor::PLAYER:
				pRoomData[index] = cSpriteEmpty;
				/*if (playerX != nullptr && playerY != nullptr && pRoomNameBefore == nullptr)
				{
					*playerX = x;
					*playerY = y;
				}*/
				pRoomEntities[index] = player;
				player->SetPosition(x, y);
				break;
			case (char)Editor::ENEMY:
				//pEntities.push_back(new Enemy(x, y, 1+ rand() % 3));
				pRoomEntities[index] = new Enemy(x, y, 3, 1 + rand() % 3);
				pRoomData[index] = cSpriteEmpty; // clear the level
				break;
			case (char)Editor::ENEMY_H:
				// delta x
				//pEntities.push_back(new Enemy(x, y, 1 + rand() % 3, 3, 0));
				pRoomEntities[index] = new Enemy(x, y, 3, 1 + rand() % 3,3, 0);
				pRoomData[index] = cSpriteEmpty; // clear the level
				break;
			case (char)Editor::ENEMY_V:
				// delta y
				//pEntities.push_back(new Enemy(x, y, 1 + rand() % 3, 0, 2));
				pRoomEntities[index] = new Enemy(x, y, 3, 1 + rand() % 3, 0, 2);
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
GameEntity* Room::UpdateEntities()
{
	GameEntity* collidedEntity = nullptr;

	int c = 0;

	std::vector<GameEntity*> tmpRoomEntities = pRoomEntities;

	for (auto entity = tmpRoomEntities.begin(); entity != tmpRoomEntities.end(); ++entity)
	{
		c++;
		if ((*entity) == nullptr)
			continue;

		Point direction = (*entity)->Update(); 

		if(direction.x == 0 && direction.y == 0)
			continue;

		Point newPos = direction + (*entity)->GetPosition();

		int currentPosIndex = 0;// GetIndexFromXY((*entity)->GetXPosition(), (*entity)->GetYPosition());

		int newPosIndex = GetIndexFromXY(newPos.x, newPos.y);

		if (tmpRoomEntities[newPosIndex] != nullptr)
		{
			//bool collisionSuccessful = (*entity)->HandleCollision(tmpRoomEntities[newPosIndex]);
			bool canMoveToNewPos = (tmpRoomEntities[newPosIndex])->HandleCollision((*entity));

			if (canMoveToNewPos)
			{
				(*entity)->SetPosition(newPos.x, newPos.y);
				pRoomEntities[newPosIndex] = pRoomEntities[currentPosIndex];
				pRoomEntities[currentPosIndex] = nullptr;
			}
		}
		else
		{
			(*entity)->SetPosition(newPos.x, newPos.y);
			pRoomEntities[newPosIndex] = pRoomEntities[currentPosIndex];
			pRoomEntities[currentPosIndex] = nullptr;
		}
		//delete newPos;
		//newPos = nullptr;
		
		/*Enemy* collidedEnemy = dynamic_cast<Enemy*>(*entity);
		if (collidedEnemy)
		{
			int _x = collidedEnemy->GetXPosition();
			int _y = collidedEnemy->GetYPosition();
			if (pRoomData[GetIndexFromXY(_x, _y)] == cSpriteWall)
			{
				collidedEnemy->ChangeDirection();
			}
		}*/

		/*
		if (x == (*entity)->GetXPosition() && y == (*entity)->GetYPosition())
		{
			// should only be able to collide with one actor
			assert(collidedEntity == nullptr);
			collidedEntity = (*entity);
		}
		*/
	}

	return collidedEntity;
}

int Room::GetIndexFromXY(int x, int y)
{
	return y * width + x;
}