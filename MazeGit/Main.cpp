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

int main()
{
    Game game;
    
    if (game.Load())
    {
        while (!game.IsGameOver())
        {
            game.Run();
        }

        std::cout << "YOU WON!!!" << std::endl;

    }
    else
    {
        std::cout << "Game did not load. Terminating now!" << std::endl;
    }    
}