#include "Game.h"
#include <iostream>
#include <conio.h>
#include "Room.h"
#include "Enemy.h"
#include "Door.h"
#include "Money.h"
#include "Exit.h"
#include <Windows.h>
#include "EventManager.h"


Game::Game(std::string levelName)
    : isGameOver(false)
    , player(Player())
    , levelName(levelName)
    , roomName("0")
{

}

Game::~Game()
{
}

bool Game::Load(std::string roomName, char *pRoomBefore)
{
    if (!level.Load(levelName, roomName))
        return false;

    bool anyWarnings = level.GetCurrentRoom()->Convert(&player, pRoomBefore);

    if (anyWarnings)
        return false;

    this->roomName = roomName;

    return true;
}

void Game::Run()
{
    // Process Inputs

    //Point playerRequestedDirection = GetPlayerInput();
        
    //UpdatePlayerPosition(playerRequestedDirection);

    // Updates Game World
    //isGameOver = UpdateGameWorld();
    // check for events
  
    UpdateGameWorld();
	// Generate Outputs
    EventManager::GetInstance()->ActivateEvents();

    Draw();
}

bool Game::IsGameOver()
{
	return isGameOver;
}


void Game::UpdatePlayerPosition(Point direction)
{
    if (!PlayerCanMoveInDirection(direction))
        return;

    (*player.GetXPositionPtr()) += direction.x;
    (*player.GetYPositionPtr()) += direction.y;

    //level.GetCurrentRoom()->
}

bool Game::UpdateGameWorld()
{
    level.GetCurrentRoom()->UpdateEntities();
    return false;
}

void Game::Draw()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    level.Draw();

    // Set cursor position for player
    COORD actorCursorPosition = { player.GetXPosition(), player.GetYPosition() };
    SetConsoleCursorPosition(console, actorCursorPosition);
    
    player.Draw();

    // Set the cursor to the end of the level
    COORD currentCursorPosition = { 0, level.GetHeight() + 1 };
    SetConsoleCursorPosition(console, currentCursorPosition);

    player.DisplayInfo();

}

bool Game::PlayerCanMoveInDirection(Point direction)
{
    int x = player.GetXPosition() + direction.x;
    int y = player.GetYPosition() + direction.y;

    //Room* r = level.GetCurrentRoom();

    // TODO: could be extended with an IsObstacle function
    return !level.GetCurrentRoom()->IsWall(x, y);
}

Point Game::GetPlayerInput()
{
    char input = _getch();
    int arrowInput = 0;
    //int newPlayerX = player.GetXPosition();
    //int newPlayerY = player.GetYPosition();
    int inputMovementX = 0;
    int inputMovementY = 0;

    if (input == cArrowInput)
    {
        arrowInput = _getch();
    }

    // 1? could also use varying user speed
    if ((input == cArrowInput && arrowInput == cArrowLeft) ||
        (char)input == 'A' || (char)input == 'a')
    {
        inputMovementX--;
    }
    else if ((input == cArrowInput && arrowInput == cArrowRight) ||
        (char)input == 'D' || (char)input == 'd')
    {
        inputMovementX = 1;
    }
    else if ((input == cArrowInput && arrowInput == cArrowDown) ||
        (char)input == 'S' || (char)input == 's')
    {
        inputMovementY = 1;
    }
    else if ((input == cArrowInput && arrowInput == cArrowUp) ||
        (char)input == 'W' || (char)input == 'w')
    {
        inputMovementY = -1;
    }
    else if (input == cEscape)
    {
        userQuit = true;
    }
    else if ((char)input == 'Z' || (char)input == 'z')
    {
        player.DropKey();
    }
    /*
        //just check ALL COLLISIONS[
        //return level.GetCurrentRoom()->UpdateEntities();
        //return HandleCollision(newPlayerX, newPlayerY);
    */
    return Point(inputMovementX, inputMovementY);
}

bool Game::HandleCollision(int newPlayerX, int newPlayerY)
{
    Room* currentRoom = level.GetCurrentRoom();
    GameEntity* collidedEntity = currentRoom->UpdateEntities();
    if (collidedEntity != nullptr && collidedEntity->IsActive())
    {
        // if player already has key and is on a tile with something in it, prevent 'zZ' key from firing
        // bad way of dealing with it
        player.BlockKeyDrop();
        // if returned pointer is invalid, collidedEntity is not Enemy and thus collidedEnemy is nullptr
        collidedEntity->HandleCollision(&player);
        // no...in realtà qualsiasi tipo di collision
        /*
        Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedEntity);
        if (collidedEnemy)
        {
            collidedEnemy->Remove(); // TODO: why? let's implement combat (with multithreading)

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
            // just to avoid checking if something is in (x,y) so to not to drop key on non-empty tile
            // if player successfully picks up key, remove it from game
            if (player.TryPickupKey(collidedKey))
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

            std::string nextRoom = collidedExit->GetNextRoomAsString();

            if (nextRoom.empty())
                return true;
            else
            {
                Load(nextRoom, roomName.empty() ? nullptr : &roomName[0]);
            }
                
        }
        */
        
    }
    else if (currentRoom->IsSpace(newPlayerX, newPlayerY)) // no collision
    {
        player.RestoreKeyDrop();
        //player.SetPosition(newPlayerX, newPlayerY);
    }
    else if (currentRoom->IsWall(newPlayerX, newPlayerY))
    {
        // wall collision, do nothing
        player.RestoreKeyDrop();
    }

    return false;
}

/*void Game::LoadRoom(char roomName)
{
    // save status of current Room

    Load()
    
    // load new room
}*/


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