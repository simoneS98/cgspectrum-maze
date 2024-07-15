#include "Player.h"
#include <stdlib.h>
#include <iostream>
#include "Room.h"

Player::Player()
	: Character(0,0,3)
	, pCurrentKey(nullptr)
	, money(0)
	, lives(2)
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



void Player::Draw()
{
	std::cout << playerSprite;
}

void Player::PickupKey(Key *key)
{
	pCurrentKey = key;
}

void Player::UseKey()
{
	pCurrentKey->Remove();
	pCurrentKey = nullptr;
}

void Player::DropKey()
{
	if (pCurrentKey)
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