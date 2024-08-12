#include "Player.h"
#include <stdlib.h>
#include <iostream>

#include <Windows.h>
#include <conio.h>
#include "Door.h"
#include "EventManager.h"
#include "PlayerDeathEvent.h"
#include "PauseGameEvent.h"
#include "Money.h"
#include <thread>
#include "DebugManager.h"
#include <functional>

Player::Player(Room* pRoom)
	: Character(0,0,pRoom,3)
	, money(0)
	, lives(2)
	, canDropKey(true)
    , m_enemiesKilled(0)
    , m_stepsTaken(0)
{
}

Player::~Player()
{
	delete pCurrentKey;
	pCurrentKey = nullptr;
}

bool Player::HasKey()
{
	return pCurrentKey != nullptr;
}

bool Player::HasKey(Color color)
{
	return HasKey() && pCurrentKey->GetColor() == color;
}

void Player::DisplayInfo()
{
    std::string border = std::string(1, (char)Sprite::PERIMETER);
    std::string label = border + " PLAYER INFO " + border;

    size_t labelSize = label.size();

    for (int i = 0; i < labelSize ; i++)
        std::cout << border;

    std::cout << std::endl << label << std::endl;

    int wrapOffset = 24;

    for (int i = 0; i < labelSize + wrapOffset; i++)
        std::cout << border;

    std::cout << std::endl;
	//std::cout << "PLAYER INFO" << std::endl;

	std::cout << border << " Current key: ";

	if (pCurrentKey == nullptr)
		std::cout << " ";
	else
		pCurrentKey->Draw();

    std::cout << " " << border << " Money: " << GetMoney() << " " << border;

    std::cout << " HP: " << hp << "/" << maxHp << " " << border << std::endl;
    
    for (int i = 0; i < labelSize + wrapOffset; i++)
        std::cout << border;

    std::cout << std::endl;

    // TODO: generic concat n times
    auto lives_str = [](int n, auto& print_message, std::string s = std::string())
        {
            if (n == 0)
                return s;
            
            return print_message(n - 1, print_message, s += std::string(1,(char)Sprite::LIFE));
            
        };

    //std::string livesLeft = border + " Lives left: " + sum(lives) + " ";

    std::string livesLeft = border + " Lives left: " + lives_str(lives, lives_str) + " ";

    std::cout << livesLeft;

    for(int i = 0; i < (labelSize + wrapOffset) - (livesLeft.size()+1)  ; i++)
        std::cout << " ";
    std::cout << border << std::endl;
    
    for (int i = 0; i < labelSize + wrapOffset; i++)
        std::cout << border;
    
    std::cout << std::endl;
}

void Player::Draw()
{
	std::cout << playerSprite;
}


void Player::UseKey()
{
	pCurrentKey->Remove();
	pCurrentKey = nullptr;
}

void Player::DropKey()
{
	if (pCurrentKey && canDropKey)
	{
        pRoom->PlaceAt(pCurrentKey, Point(pPosition->x, pPosition->y));
        //delete pCurrentKey;
        pCurrentKey = nullptr;
	}
}

void Player::Die()
{
	lives--;

    if (lives == 0)
    {
        EventManager::GetInstance()->Add(new PlayerDeathEvent());
    }
    else
    {
        // TODO: reset position
        hp = maxHp;
    }
}

Point Player::Update()
{
    // TODO: use thread to add input to EventManager
    Point inputDirection = GetInput();

    //inputDirection += GetPosition();

    return inputDirection;
}

bool Player::CollideWith(GameEntity* collidedEntity)
{
    return true;
}

/*
DebugCommand[] debugcommands = {...}

DebugCommand{
    GODMODE = 0, TRAVERSE_EVERYTHING = 1
}

debugcommands[TRAVERSE_EVERYTHING]
*/

// only implemented in Player class
bool Player::TryUseKeyOn(GameEntity* lockedEntity)
{
    #ifdef _DEBUG
    if(DebugManager::GetInstance()->IsPlayerInvicible())
        return true;
    #endif
    if (pCurrentKey == nullptr)
        return false;

    if (pCurrentKey->GetColor() == lockedEntity->GetColor())
    {
        //UseKey();
        dynamic_cast<Door*>(lockedEntity)->Unlock();
        UseKey();
        return true;
    }

    return false;
}

void Player::PickupMoney(GameEntity* money)
{
    AddMoney(((Money*)money)->GetWorth());
    pRoom->RemoveFrom(money, money->GetPosition());
}

Point Player::GetInput()
{
    char cArrowInput = (char)Input::ARROW_IN;
    char cArrowLeft = (char)Input::ARROW_LEFT;
    char cArrowRight = (char)Input::ARROW_RIGHT;
    char cArrowDown = (char)Input::ARROW_DOWN;
    char cArrowUp = (char)Input::ARROW_UP;
    char cEscape = (char)Input::ESC;

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
        EventManager::GetInstance()->Add(new PauseGameEvent());
        //userQuit = true;
    }
    else if ((char)input == 'Z' || (char)input == 'z')
    {
        //EventManager::GetInstance()->Add(new SpawnEvent(pCurrentKey,pPosition));
        DropKey();
    }
    /*
        //just check ALL COLLISIONS[
        //return level.GetCurrentRoom()->UpdateEntities();
        //return HandleCollision(newPlayerX, newPlayerY);
    */
    return Point(inputMovementX, inputMovementY);
    
}