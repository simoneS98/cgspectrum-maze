#include "Character.h"
#include "Door.h"

Character::Character(int x, int y, int maxHp)
	: GameEntity(x,y)
	, maxHp(maxHp)
	, pCurrentKey(nullptr)
{
	hp = maxHp;
}

int Character::GetMaxHp()
{
    return maxHp;
}

int Character::GetCurrentHp()
{
    return hp;
}

void Character::TakeDamage(int amount)
{
	hp -= amount;
	if (hp <= 0)
		Die();
}


bool Character::TryPickupKey(GameEntity* key)
{
	if (pCurrentKey != nullptr)
		return false;

	pCurrentKey = (Key*)key;
	return true;
}


void Character::Die()
{
	//find a way to invoke event
	//system("cls");
	//std::cout << "Your HP reached 0! Game over." << std::endl;
	//exit(1);
}