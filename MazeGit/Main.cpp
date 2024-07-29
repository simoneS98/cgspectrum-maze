// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "vld.h"
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
#include "AudioManager.h"
#include "EventManager.h"
#include "PlayerDeathEvent.h"

using namespace std;

int main()
{   
    cout << "Which level do you want to play? (TODO: print list of levels)";

    string levelName;

    cin >> levelName;

    Game game = Game(levelName);
    
    if (game.Load())
    {
        AudioManager::GetInstance()->PlayStartGameSound();
        while (!game.IsGameOver())
        {
            game.Run();
        }

        if (game.DidUserQuit())
            cout << "Thanks for playing!" << endl;
        else if (game.GetPlayerLives() < 0)
            cout << "YOU LOSE!!!!" << endl;
        else
            cout << "YOU WIN!!!" << endl;
    }
    else
    {
        std::cout << "Game did not load. Terminating now!" << std::endl;
    }    

    AudioManager::DestroyInstance();
}