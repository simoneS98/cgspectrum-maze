#include "Player.h"
#include <stdlib.h>
#include <iostream>
#include "Room.h"

Player::Player()
	: Character(0,0,3)
	, pCurrentKey(nullptr)
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

	std::cout << std::endl;
}

void Player::Draw()
{
	std::cout << playerSprite;
}

bool Player::TryPickupKey(Key *key)
{
	if (pCurrentKey != nullptr)
		return false;
		
	pCurrentKey = key;
	return true;
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