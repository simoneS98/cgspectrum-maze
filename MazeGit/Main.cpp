// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if __has_include("vld.h")
//#include "vld.h"
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
#include "Enemy.h"
#include "Wall.h"

using namespace std;

int main()
{     
    Game* pGame = new Game();

    StateMachineExampleGame* stateMachineInstance = StateMachineExampleGame::GetInstance();

    stateMachineInstance->Init(pGame);

    while (true)
    {
        // decouple menuOption selection by using events
        //EventManager::GetInstance()->ActivateEvents(pGame);
        //stateMachineInstance->DrawCurrentState();
        stateMachineInstance->UpdateCurrentState();
    }

    EventManager::DestroyInstance();
    AudioManager::DestroyInstance(); 
}