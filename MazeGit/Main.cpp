// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if __has_include("vld.h")
#include "vld.h"
#endif

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
#include "StateMachineExampleGame.h"

using namespace std;

int main()
{   
  
    Game* pGame = new Game();

    StateMachineExampleGame stateMachine = StateMachineExampleGame(pGame);
    
    stateMachine.Init();

    while (true)
    {
        // decouple menuOption selection by using events
        EventManager::GetInstance()->ActivateEvents(pGame);
        stateMachine.DrawCurrentState();
        stateMachine.UpdateCurrentState();
    }

    /*
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
    }*/

    AudioManager::DestroyInstance();
}