#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <thread>
#include "EventManager.h"
#include "LevelManager.h"
#include <fstream>
#include "StateMachineExampleGame.h"
#include "ExitGameEvent.h"

Game::Game()
    : isGameOver(false)
    , roomName("0")
{
}

Game::Game(std::string levelName)
    : isGameOver(false)
    , levelName(levelName)
    , roomName("0")
{
    LevelManager::GetInstance()->SetLevelName(levelName);
}

Game::~Game()
{
    delete player;
    player = nullptr;
}

bool Game::Save()
{
    LevelManager::GetInstance()->Save();
    return true;
}

bool Game::Load(std::string roomName, char* pRoomBefore)
{
    char roomBefore = NULL;

    if (pRoomBefore != nullptr)
        roomBefore = pRoomBefore[0];// *pRoomBefore;

    //roomBefore = (LevelManager::GetInstance()->GetCurrentRoom()->GetName())[0];

    if (!LevelManager::GetInstance()->Load(roomName))
        return false;

    this->roomName = roomName;

    Room* currRoom = LevelManager::GetInstance()->GetCurrentRoom();

    bool anyWarnings = currRoom->Convert(this->player, roomBefore);

    if (anyWarnings)
        return false;

    return true;
}

bool Game::Load(Player*& pPlayer, std::string roomName, char* pRoomBefore)
{
    char roomBefore = NULL;
    
    if(pRoomBefore != nullptr)
        roomBefore = *pRoomBefore;

    if (!LevelManager::GetInstance()->Load(roomName))
        return false;

        pPlayer = new Player(LevelManager::GetInstance()->GetCurrentRoom());

    this->roomName = roomName;

    Room* currRoom = LevelManager::GetInstance()->GetCurrentRoom();

    //if (player == nullptr)
        player = pPlayer;//new Player(currRoom);

    bool anyWarnings = currRoom->Convert(player, roomBefore);

    if (anyWarnings)
        return false;

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
  
   // UpdateGameWorld();
    LevelManager::GetInstance()->GetCurrentRoom()->UpdateEntities();

	// Generate Outputs
    //EventManager::GetInstance()->ActivateEvents(this);

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

    (*player->GetXPositionPtr()) += direction.x;
    (*player->GetYPositionPtr()) += direction.y;

    //level.GetCurrentRoom()->
}

bool Game::UpdateGameWorld()
{
    LevelManager::GetInstance()->GetCurrentRoom()->UpdateEntities();
    //level.GetCurrentRoom()->UpdateEntities();
    return false;
}

void Game::Draw()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    //level.Draw();
    LevelManager::GetInstance()->GetCurrentRoom()->Draw();

    // Set cursor position for player
    //COORD actorCursorPosition = { player->GetXPosition(), player->GetYPosition() };
    //SetConsoleCursorPosition(console, actorCursorPosition);
    
    //player->Draw();

    // Set the cursor to the end of the level
    //COORD currentCursorPosition = { 0, level.GetHeight() + 1 };
    //SetConsoleCursorPosition(console, currentCursorPosition);

    player->DisplayInfo();

}

bool Game::PlayerCanMoveInDirection(Point direction)
{
    int x = player->GetXPosition() + direction.x;
    int y = player->GetYPosition() + direction.y;

    //Room* r = level.GetCurrentRoom();

    // TODO: could be extended with an IsObstacle function
    return !LevelManager::GetInstance()->GetCurrentRoom()->IsWall(x, y);
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
        player->DropKey();
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
    Room* currentRoom = LevelManager::GetInstance()->GetCurrentRoom();
    GameEntity* collidedEntity = currentRoom->UpdateEntities();
    if (collidedEntity != nullptr && collidedEntity->IsActive())
    {
        // if player already has key and is on a tile with something in it, prevent 'zZ' key from firing
        // bad way of dealing with it
        player->BlockKeyDrop();
        // if returned pointer is invalid, collidedEntity is not Enemy and thus collidedEnemy is nullptr
        collidedEntity->CollideWith(player);
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
        player->RestoreKeyDrop();
        //player.SetPosition(newPlayerX, newPlayerY);
    }
    else if (currentRoom->IsWall(newPlayerX, newPlayerY))
    {
        // wall collision, do nothing
        player->RestoreKeyDrop();
    }

    return false;
}

void Game::DisplayAndSaveStats(std::string fileName, std::string playerName, int stepsTaken, int enemiesKilled, int livesLeft, int money)
{
    std::cout << "Here is your stats : " << std::endl;
    std::cout << "Amount of steps taken: " << stepsTaken << std::endl;
    std::cout << "Amount of enemies killed: " << enemiesKilled << std::endl;
    std::cout << "Remaining lives: " << livesLeft << std::endl;
    std::cout << "Money collected: " << money << std::endl;

    std::cout << std::endl;

    std::cout << "Saving progress on leaderboard..." << std::endl;

    std::ofstream levelFile;

    levelFile.open(fileName, std::ios_base::app);

    if (!levelFile)
    {
        std::cout << "[LeaderBoard] Opening file failed!" << std::endl;
    }
    else
    {
        // TODO: use class to read/write data
        levelFile << "name=" << playerName << std::endl;
        levelFile << "steps=" << stepsTaken << std::endl;
        levelFile << "enemies_killed=" << enemiesKilled << std::endl;
        levelFile << "lives_left=" << livesLeft << std::endl;
        levelFile << "money=" << money << std::endl;
        levelFile << ";" << std::endl;

        if (!levelFile)
        {
            std::cout << "[LeaderBoard] Write failed!" << std::endl;
        }

        std::cout << "Leaderboard updated!" << std::endl;

        levelFile.close();
    }
}

void Game::SaveScore()
{
    std::string levelName = LevelManager::GetInstance()->GetLevelName();
    std::string basePath = "levels/" + levelName + "/";

    // this is working directory for the current level
    basePath.insert(0, "../");

    system("cls");

    std::cout << "Congrats for finishing the game! Please enter your name: " << std::endl;

    std::string playerName;

    std::cin >> playerName;

    std::string fileName = basePath + "leaderboard.txt";

    DisplayAndSaveStats(fileName, playerName, player->GetStepsTaken(), player->GetEnemiesKilled(), player->GetLives(), player->GetMoney());

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    auto waitBeforeExitingToMainMenu = [console](int countDown) {

        while (countDown > 0)
        {
            std::cout << "Exiting to main menu in ";
            SetConsoleTextAttribute(console, (int)Color::RED);
            std::cout << countDown;
            SetConsoleTextAttribute(console, (int)Color::DEFAULT); 
            std::cout << "..." << "\r";
            countDown--;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        EventManager::GetInstance()->Add(new ExitGameEvent("Score added to leaderboard"));
    };

    std::thread waitThread(waitBeforeExitingToMainMenu, 5);
    waitThread.join();

}
