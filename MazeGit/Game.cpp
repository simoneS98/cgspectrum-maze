#include "Game.h"
#include <iostream>
#include <conio.h>
#include "Room.h"
#include "Enemy.h"
#include "Door.h"
#include "Money.h"
#include "Exit.h"
#include <Windows.h>

Game::Game()
    : isGameOver(false)
    , player(Player())
{
	//level.Load()
}

Game::~Game()
{
}

bool Game::Load(std::string levelName)
{
	return level.Load(levelName);
}

void Game::Run()
{
	Draw();

	isGameOver = Update();

	/*
    if (isGameOver)
		Draw();
    */
}

bool Game::IsGameOver()
{
	return isGameOver;
}

bool Game::Update()
{
    char input = _getch();
    int arrowInput = 0;
    int newPlayerX = player.GetXPosition();
    int newPlayerY = player.GetYPosition();
    int moveX = 0;
    int moveY = 0;

    if (input == cArrowInput)
    {
        arrowInput = _getch();
    }

    if ((input == cArrowInput && arrowInput == cArrowLeft) ||
        (char)input == 'A' || (char)input == 'a')
    {
        newPlayerX--;
    }
    else if ((input == cArrowInput && arrowInput == cArrowRight) ||
        (char)input == 'D' || (char)input == 'd')
    {
        newPlayerX++;
    }
    else if((input == cArrowInput && arrowInput == cArrowDown) ||
        (char)input == 'S' || (char)input == 's')
    {
        newPlayerY++;
    }
    else if ((input == cArrowInput && arrowInput == cArrowUp) ||
        (char)input == 'W' || (char)input == 'w')
    {
        newPlayerY--;
    }
    else if(input == cEscape)
    {
        userQuit = true;
        return true;
    }
    else if ((char)input == 'Z' || (char)input == 'z')
    {
        player.DropKey();
    }

    // If position never changed
    if (newPlayerX == player.GetXPosition() && newPlayerY == player.GetYPosition())
    {
        return false;
    }
    else
    {
        return HandleCollision(newPlayerX, newPlayerY);
    }
}

void Game::Draw()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    
    level.GetCurrentRoom()->Draw();

    // Set cursor position for player
    COORD actorCursorPosition = { player.GetXPosition(), player.GetYPosition() };
    SetConsoleCursorPosition(console, actorCursorPosition);

    // Set the cursor to the end of the level
    COORD currentCursorPosition = { 0, level.GetHeight() };
    SetConsoleCursorPosition(console, currentCursorPosition);

}

bool Game::HandleCollision(int newPlayerX, int newPlayerY)
{
    Room* currentRoom = level.GetCurrentRoom();
    GameEntity* collidedEntity = currentRoom->UpdateEntities(newPlayerX,newPlayerY);
    if (collidedEntity != nullptr && collidedEntity->IsActive())
    {
        // if returned pointer is invalid, colldedEntity is not Enemy and thus collidedEnemy is nullptr
        Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedEntity);
        if (collidedEnemy)
        {
            collidedEnemy->Remove();

            player.SetPosition(newPlayerX, newPlayerY);

            player.TakeDamage(collidedEnemy->GetDamage());
            // gnnneh
            if (player.GetLives() < 0)
            {
                return true;
            }
        }

        Money* collidedMoney = dynamic_cast<Money*>(collidedEntity);
        if (collidedMoney)
        {
            collidedMoney->Remove();
            player.AddMoney(collidedMoney->GetWorth());
            player.SetPosition(newPlayerX, newPlayerY);

        }

        Key* collidedKey = dynamic_cast<Key*>(collidedEntity);
        if (collidedKey)
        {
            player.PickupKey(collidedKey);
            collidedKey->Remove();
            player.SetPosition(newPlayerX, newPlayerY);

        }

        Door* collidedDoor = dynamic_cast<Door*>(collidedEntity);
        if (collidedDoor)
        {
            if (collidedDoor->IsLocked()) {
                if (player.HasKey(collidedDoor->GetColor()))
                {
                    collidedDoor->Unlock();
                    player.UseKey();
                    collidedDoor->Remove();
                    player.SetPosition(newPlayerX, newPlayerY);
                }
            }
            else {
                player.SetPosition(newPlayerX, newPlayerY);
            }
            
        }

        Exit* collidedExit = dynamic_cast<Exit*>(collidedEntity);
        if (collidedExit)
        {
            collidedExit->Remove();
            player.SetPosition(newPlayerX, newPlayerY);

            Room* nextRoom = collidedExit->GetNextRoom();

            if (nextRoom == nullptr)
                return true;
            else
                LoadRoom(nextRoom);
        }
    }
    else if (currentRoom->IsSpace(newPlayerX, newPlayerY)) // no collision
    {
        player.SetPosition(newPlayerX, newPlayerY);
    }
    else if (currentRoom->IsWall(newPlayerX, newPlayerY))
    {
        // wall collision, do nothing
    }

    return false;
}

void Game::LoadRoom(Room* room)
{
    // save status of current Room

    // load room
}


/*

void PlayDoorClosedSound()
{
    Beep(500, 75);
    Beep(500, 75);
}

void PlayDoorOpenSound()
{
    Beep(1397, 200);
}

void PlayKeyPickupSound()
{
    Beep(1568, 200);
}

void PlayWinSound()
{
    Beep(1568, 200);
    Beep(1568, 200);
    Beep(1568, 200);
    Beep(1245, 1000);
    Beep(1397, 200);
    Beep(1397, 200);
    Beep(1397, 200);
    Beep(1397, 200);
    Beep(1157, 1000);
}
*/