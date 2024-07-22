#include "Player.h"
#include <stdlib.h>
#include <iostream>
#include "Room.h"
#include <Windows.h>
#include <conio.h>
#include "Door.h"
#include "EventManager.h"
#include "SpawnEvent.h"

Player::Player()
	: Character(0,0,3)
	, money(0)
	, lives(2)
	, canDropKey(true)
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


/*
int Player::GetNumKeys()
{
	return numKeys;
}
*/



void Player::DisplayInfo()
{
	std::cout << "PLAYER INFO" << std::endl;

	std::cout << "Current key: ";

	if (pCurrentKey == nullptr)
		std::cout << "none";
	else
		pCurrentKey->Draw();

	std::cout << "\t" << "Money: " << GetMoney();

    std::cout << "\t" << "HP: " << hp << "/" << maxHp << std::endl;

    std::cout << "Lives left: ";

    for (int i = 0; i < lives; i++)
    {
        std::cout << "*";
    }

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
		pCurrentKey->Place(pPosition->x, pPosition->y);
		pCurrentKey = nullptr;
	}
}

void Player::Die()
{
	lives--;
	//find a way to invoke event
	//system("cls");
	//std::cout << "Your HP reached 0! Game over." << std::endl;
	//exit(1);
}

Point Player::Update()
{
    Point inputDirection = GetInput();

    //inputDirection += GetPosition();

    return inputDirection;
}

bool Player::HandleCollision(GameEntity* collidedEntity)
{
    return true;
}

// only implemented in Player class
bool Player::TryUseKeyOn(GameEntity* lockedEntity)
{
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
        //userQuit = true;
    }
    else if ((char)input == 'Z' || (char)input == 'z')
    {
        EventManager::GetInstance()->Add(new SpawnEvent(pCurrentKey,pPosition));
        //DropKey();
    }
    /*
        //just check ALL COLLISIONS[
        //return level.GetCurrentRoom()->UpdateEntities();
        //return HandleCollision(newPlayerX, newPlayerY);
    */
    return Point(inputMovementX, inputMovementY);
    
}