// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include "Player.h"
#include "Enums.h"
#include "Level.h"
#include "FileUtils.h"
#include "Game.h"

using namespace std;

int GetIndexFromCoordinates(int x, int y, int width);

bool UpdatePlayerPosition(Level* level, Player* player);

//responsible of checking for obstacles/keys/etc. and updating player's position accordingly
bool MoveTowards(Level* pLevel, Player* player, int nextX, int nextY);

bool IsObstacle(char c);

bool IsEndOfMap(int x, int y, int width, int height);

void PlayDoorClosedSound();
void PlayDoorOpenSound();
void PlayKeyPickupSound();
void PlayWinSound();

void DisplayPlayerInfo(Player* player);
void DisplayLevel(Level* pLevel, Player* player);
int GetIndexFromXY(int x, int y, int width);
void DisplayTopBorder(int width);
void DisplayBottomBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();
void DisplayHorizontalBorder(int width);
void DisplayVerticalBorder();
void DisplayRoom(char* pLevel, int index);

int main()
{
    Game game;

    if (game.Load())
    {
        while (!game.IsGameOver())
        {
            game.Run();
        }

        cout << "YOU WON!!!" << endl;

    }
    else
    {
        cout << "Game did not load. Terminating now!" << endl;
    }
    bool endGame = false;
    Player* player = new Player();

    Level* pLevel = FileUtils::FileToLevel("map.txt");//LoadLevel("map.txt");

    while (!endGame)
    {
        system("cls");
        DisplayPlayerInfo(player);
        DisplayLevel(pLevel, player);
        endGame = UpdatePlayerPosition(pLevel, player);
    }

    cout << "You made it! Congrats!" << endl;
}

int GetIndexFromCoordinates(int x, int y, int width)
{
    return y * width + x;
}

bool UpdatePlayerPosition(Level* level, Player* player)
{
    char input = _getch();

    int moveX = 0;
    int moveY = 0;

    switch (input)
    {
    case 'w':
    case 'W':
        moveX = -1;
        break;
    case 's':
    case 'S':
        moveX = 1;
        break;
    case 'a':
    case 'A':
        moveY = -1;
        break;
    case 'd':
    case 'D':
        moveY = 1;
        break;
    default:
        break;
    }

    int nextX = player->GetXPos() + moveX;
    int nextY = player->GetYPos() + moveY;

    int height = level->GetHeight();
    int width = level->GetWidth();

    if (nextX < 0)
        nextX = 0;
    else if (nextX == height)
        nextX = height - 1;
    else if (nextY < 0)
        nextY = 0;
    else if (nextY == width)
        nextY = width - 1;

    return MoveTowards(level, player, nextX, nextY);

}

//TODO: use player struct
bool MoveTowards(Level* pLevel, Player* player, int nextX, int nextY)
{
    bool exitReached = false;

    Room* nextRoom = pLevel->GetRoom(nextX, nextY);

    bool playerCanEnter = nextRoom->IsAccessible();

    if (playerCanEnter)
    {
        player->SetPos(nextX, nextY);
        nextRoom->OnEnter(player);
    }
        
    
    /*
    if (IsObstacle(nextTile))
    return false;
    */

    // object magic! no more ifs!

    /*
    if (nextTile == RoomType::DOOR)
    {
        if (player->UseKey()) {
            level.map[nextIndex] = ' ';
        }
        else
        {
            PlayDoorClosedSound();
            return false;
        } 
    }
    else if (nextTile == RoomType::KEY)
    {
        player->PickupKey();
        level.map[nextIndex] = ' ';
    }
    else if (nextTile == RoomType::SPIKES)
    {
        player->TakeDamage(1);
    }
    */
    
    /*else if (nextTile == kExit)
    {
        int playerIndex = GetIndexFromCoordinates(playerX, playerY, width);
        map[playerIndex] = ' ';
        exitReached = true;
    }*/

    
    return exitReached;
}

bool IsObstacle(char c)
{
    //return c == cBlock;
    return false;
}

bool IsEndOfMap(int col, int row, int width, int height)
{
    return (col < 0 || col > width - 1) || (row < 0 || row > height - 1);
}

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

bool CheckForGameOver(char map[], int posX, int posY)
{
    return map[posX];
}

void DisplayPlayerInfo(Player* player)
{
    cout << " Keys: " << player->GetNumKeys() << "\tHealth Points: " << player->GetCurrentHp() << " / " << player->GetMaxHp() << endl;
}

//TODO: move display functions to level class
void DisplayLevel(Level* pLevel, Player* player)
{
    int width = pLevel->GetWidth();
    int height = pLevel->GetHeight();

    DisplayHorizontalBorder(width);

    for (int x = 0; x < height; x++)
    {
        DisplayLeftBorder();
        for (int y = 0; y < width; y++)
        {
            if (player->GetXPos() == x && player->GetYPos() == y)
            {
                cout << (char)RoomType::PLAYER;
            }
            else
            {
                Room room = *(pLevel->GetRoom(x, y));

                room.Display();
            }
        }
        DisplayRightBorder();
    }

    DisplayHorizontalBorder(width);
}

void DisplayTopBorder(int width)
{
    /*
    cout << cWallTopLeftCorner;

    DisplayHorizontalBorder(width);

    cout << cWallTopRightCorner << endl;
    */
}

void DisplayBottomBorder(int width)
{
    /*
    cout << cWallBottomLeftCorner;

    DisplayHorizontalBorder(width);

    cout << cWallBottomRightCorner << endl;
    */
    
}

void DisplayLeftBorder()
{
    DisplayVerticalBorder();
}

void DisplayRightBorder()
{
    DisplayVerticalBorder();
    cout << endl;
}

void DisplayVerticalBorder()
{
    cout << (char)RoomType::WALL;
}

void DisplayHorizontalBorder(int width)
{
    // -1 and +1 to take care of left and right corners
    for (int i = -1 ; i < width + 1 ; i++)
    {
        cout << (char)RoomType::WALL;
    }

    cout << endl;
}
