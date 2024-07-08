#include "Player.h"
#include <stdlib.h>
#include <iostream>

Player::Player()
{
	x = 0;
	y = 0;
	maxHp = 5;
	hp = maxHp;
	numKeys = 0;
}

int Player::GetXPos()
{
	return x;
}

int Player::GetYPos()
{
	return y;
}

int Player::GetNumKeys()
{
	return numKeys;
}

int Player::GetMaxHp()
{
	return maxHp;
}

int Player::GetCurrentHp()
{
	return hp;
}

// Setters

void Player::SetPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Player::SetXPos(int x)
{
	this->x = x;
}

void Player::SetYPos(int y)
{
	this->y = y;
}


void Player::TakeDamage(int amount)
{
	hp -= amount;
	if (hp <= 0)
		Die();
}

void Player::PickupKey()
{
	numKeys++;
}

bool Player::UseKey()
{
	if (numKeys <= 0)
		return false;

	numKeys--;

	return true;
}

void Player::Die()
{
	//find a way to invoke event
	system("cls");
	std::cout << "Your HP reached 0! Game over." << std::endl;
	exit(1);
}