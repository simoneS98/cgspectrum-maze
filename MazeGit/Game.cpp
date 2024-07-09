#include "Game.h"
#include <iostream>
#include <conio.h>

Game::Game()
    : isGameOver(false)
{
	//level.Load()
}

Game::~Game()
{
}

bool Game::Load()
{
	return level.Load("map.txt");
}

void Game::Run()
{
	Draw();

	isGameOver = Update();

	if (isGameOver)
		Draw();
}

bool Game::IsGameOver()
{
	return isGameOver;
}

bool Game::Update()
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

    int nextX = player.GetXPos() + moveX;
    int nextY = player.GetYPos() + moveY;

    int height = level.GetHeight();
    int width = level.GetWidth();

    if (nextX < 0)
        nextX = 0;
    else if (nextX == height)
        nextX = height - 1;
    else if (nextY < 0)
        nextY = 0;
    else if (nextY == width)
        nextY = width - 1;

    bool exitReached = false;

    Room* nextRoom = level.GetRoom(nextX, nextY);

    bool playerCanEnter = nextRoom->IsAccessibleBy(&player);

    if (playerCanEnter)
    {
        player.SetPos(nextX, nextY);
        nextRoom->OnEnter(&player);
    }

    return exitReached;
    //return MoveTowards(level, player, nextX, nextY);
}
/*
bool MoveTowards(Level pLevel, Player player, int nextX, int nextY)
{
    bool exitReached = false;

    Room* nextRoom = pLevel.GetRoom(nextX, nextY);

    bool playerCanEnter = nextRoom->IsAccessibleBy(player);

    if (playerCanEnter)
    {
        player->SetPos(nextX, nextY);
        nextRoom->OnEnter(player);
    }

    return exitReached;
}
*/


void Game::Draw()
{
    system("cls");
    std::cout << " Keys: " << player.GetNumKeys() << "\tHealth Points: " << player.GetCurrentHp() << " / " << player.GetMaxHp() << std::endl;

    //TODO: move everything inside Level class
   
    int width = level.GetWidth();
    int height = level.GetHeight();

    level.DisplayHorizontalBorder();

    for (int x = 0; x < height; x++)
    {
        level.DisplayLeftBorder();
        for (int y = 0; y < width; y++)
        {
            if (player.GetXPos() == x && player.GetYPos() == y)
            {
                std::cout << (char)RoomContent::PLAYER;
            }
            else
            {
                Room room = *(level.GetRoom(x, y));

                room.Display();
            }
        }
        level.DisplayRightBorder();
    }

    level.DisplayHorizontalBorder();
    
}
