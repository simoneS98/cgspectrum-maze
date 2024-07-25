#include "Room.h"
#include <iostream>
#include <windows.h>  
#include <Constants.h>
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Exit.h"
#include "Enemy.h"
#include "Wall.h"
#include <assert.h>
#include "AudioManager.h"



Room::Room(int width, int height, char* pRoomData)
	: width(width)
	, height(height)
	, pRoomData(pRoomData)
{
	//pRoomEntities = new GameEntity*[width * height];
	pRoomEntities = std::vector<Tile>(width * height, Tile());
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
	SetConsoleTextAttribute(console, (int)cDefaultColor);

	int h = 0;
	for (auto tile = pRoomEntities.begin(); tile != pRoomEntities.end(); ++tile)
	{
		(*tile).Draw();
		h++;
		if (h % width == 0)
			std::cout << std::endl;
	}
	std::cout << std::endl;
	// Draw the Room
	/*
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int indexToPrint = GetIndexFromXY(x,y);

			Tile t = pRoomEntities[indexToPrint];

			if (t.IsEmpty())
			{
				// of course is it better to use walls as gameentities...
				// ...and leave empty spaces as nullptrs
				std::cout << pRoomData[indexToPrint];
			}
			else
			{
				t.Draw();
			}
		}
		std::cout << std::endl;
	}
	*/


	COORD entityCursorPosition;

	// Draw Entities
	/*
		front() access the first element
		back() access the last element
		end() returns an iterator to the end
		begin() returns an iterator to the beginning
	*/
	/*
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
	*/
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

bool Room::IsWall(int index)
{
	return pRoomData[index] == cSpriteWall;
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
				pRoomData[index] = cSpriteEmpty;
				pRoomEntities[index] = Tile(new Wall(x,y,this), nullptr);
				break;
			case (char)Editor::KEY_GREEN:
				pRoomData[index] = cSpriteEmpty;
				pRoomEntities[index] = Tile(nullptr, new Key(x, y, this, Color::GREEN));
				//pEntities.push_back(new Key(x, y, Color::GREEN));
				break;
			case (char)Editor::KEY_RED:
				pRoomData[index] = cSpriteEmpty;
				pRoomEntities[index] = Tile(nullptr, new Key(x, y, this, Color::RED));
				//pEntities.push_back(new Key(x, y, Color::RED));
				break;
			case (char)Editor::KEY_BLUE:
				pRoomData[index] = cSpriteEmpty;
				pRoomEntities[index] = Tile(nullptr, new Key(x, y, this, Color::BLUE));
				//pEntities.push_back(new Key(x, y, Color::BLUE));
				break;
			case (char)Editor::DOOR_RED:
				pRoomData[index] = cSpriteEmpty;
				pRoomEntities[index] = Tile(new Door(x, y, this, Color::RED), nullptr);
				//pEntities.push_back(new Door(x, y, Color::RED));
				break;
			case (char)Editor::DOOR_GREEN:
				pRoomData[index] = cSpriteEmpty;
				pRoomEntities[index] = Tile(new Door(x, y, this, Color::GREEN), nullptr);
				//pEntities.push_back(new Door(x, y, Color::GREEN));
				break;
			case (char)Editor::DOOR_BLUE:
				pRoomData[index] = cSpriteEmpty;
				pRoomEntities[index] = Tile(new Door(x, y, this, Color::BLUE), nullptr);
				//pEntities.push_back(new Door(x, y, Color::BLUE));
				break;
			case (char)Editor::MONEY:
				pRoomData[index] = cSpriteEmpty;
				//pRoomEntities[index] = new Money(x, y, this, 1 + rand() % 5);
				
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
				pRoomEntities[index] = Tile(new Exit(x, y, this, tile), nullptr);
				//pEntities.push_back(new Exit( x, y, tile));
				break;
			case (char)Editor::PLAYER:
				pRoomData[index] = cSpriteEmpty;
				/*if (playerX != nullptr && playerY != nullptr && pRoomNameBefore == nullptr)
				{
					*playerX = x;
					*playerY = y;
				}*/
				player->SetPosition(x, y);
				pRoomEntities[index] = Tile(player, nullptr);

				break;
			case (char)Editor::ENEMY:
				//pEntities.push_back(new Enemy(x, y, 1+ rand() % 3));
				pRoomEntities[index] = Tile(new Enemy(x, y, this, 3, 1 + rand() % 3), nullptr);
				pRoomData[index] = cSpriteEmpty; // clear the level
				break;
			case (char)Editor::ENEMY_H:
				// delta x
				//pEntities.push_back(new Enemy(x, y, 1 + rand() % 3, 3, 0));
				pRoomEntities[index] = Tile(new Enemy(x, y, this, 3, 1 + rand() % 3,3, 0), nullptr);
				pRoomData[index] = cSpriteEmpty; // clear the level
				break;
			case (char)Editor::ENEMY_V:
				// delta y
				//pEntities.push_back(new Enemy(x, y, 1 + rand() % 3, 0, 2));
				pRoomEntities[index] = Tile(new Enemy(x, y, this, 3, 1 + rand() % 3, 0, 2), nullptr);
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

	for (auto tile = pRoomEntities.begin(); tile != pRoomEntities.end(); ++tile)
	{
		GameEntity* entity = (*tile).GetActive();

		if (entity == nullptr)
			continue;

		entity->RefreshActivation();
	}

	//std::vector<Tile> tmpRoomEntities = pRoomEntities;

	for (auto tile = pRoomEntities.begin(); tile != pRoomEntities.end(); ++tile)
	{
		if ((*tile).IsEmpty())
			continue;

		GameEntity* entity = (*tile).GetActive();

		if (entity == nullptr)
			continue;

		if (!entity->CanActivate())
			continue;
		
		entity->StartActivation();

		Point direction = entity->Update();

		if(direction.x == 0 && direction.y == 0)
			continue;

		Point newPos = direction + entity->GetPosition();

		int currentPosIndex = GetIndexFromXY(entity->GetXPosition(), entity->GetYPosition());

		int newPosIndex = GetIndexFromXY(newPos.x, newPos.y);

		Tile& t2 = pRoomEntities[newPosIndex];

		if ( !t2.IsEmpty())
		{
			bool collisionSuccessful = HandleCollision(entity, t2);
			if (collisionSuccessful)
			{
				entity->SetPosition(newPos.x, newPos.y);
				// place current entity above the one in newPosIndex
				t2.Add(entity);
				if(pRoomEntities[currentPosIndex].GetActive() != nullptr)
					pRoomEntities[currentPosIndex].RemoveActive();
				else
					pRoomEntities[currentPosIndex].RemovePassive();
			}	
		}
		else
		{				
			entity->SetPosition(newPos.x, newPos.y);
			pRoomEntities[newPosIndex].Add(entity);
			if (pRoomEntities[currentPosIndex].GetActive() != nullptr)
				pRoomEntities[currentPosIndex].RemoveActive();
			else
				pRoomEntities[currentPosIndex].RemovePassive();
		}
	}

	
	//pRoomEntities = tmpRoomEntities;

	return collidedEntity;
}

int Room::GetIndexFromXY(int x, int y)
{
	return y * width + x;
}

bool Room::HandleCollision(GameEntity* g1, GameEntity* g2)
{
	bool activeCollision = g1->CollideWith(g2);
	bool reactiveCollision = g2->CollideWith(g1);

	return activeCollision && reactiveCollision;
}

bool Room::HandleCollision(GameEntity* g1, Tile& destinationTile)
{
	bool activeCollision = true;
	bool reactiveCollision = false;

	if (destinationTile.GetActive() != nullptr)
	{
		activeCollision = g1->CollideWith(destinationTile.GetActive());
		reactiveCollision = destinationTile.GetActive()->CollideWith(g1);
	}	
	else if (destinationTile.GetPassive() != nullptr)
	{
		activeCollision = g1->CollideWith(destinationTile.GetPassive());
		reactiveCollision = destinationTile.GetPassive()->CollideWith(g1);
		if (reactiveCollision)
		{
			destinationTile.RemovePassive();
		}
			
	}

	return activeCollision && reactiveCollision;
}

bool Room::PlaceAt(GameEntity* gameEntity, Point p)
{
	int index = GetIndexFromXY(p.x, p.y);
	/*if (pRoomEntities[index] != nullptr)
		return false;*/
	pRoomEntities[index].Add(gameEntity);
	return true;
}

void Room::MoveEntity(Point startPos, Point endPos)
{
	int startPosIndex = GetIndexFromXY(startPos.x,startPos.y);
	int endPosIndex = GetIndexFromXY(endPos.x, endPos.y);

	pRoomEntities[endPosIndex] = pRoomEntities[startPosIndex];
	pRoomEntities[startPosIndex] = nullptr;
}
