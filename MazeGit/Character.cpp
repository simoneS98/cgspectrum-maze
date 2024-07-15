#include "Character.h"

Character::Character(int x, int y, int maxHp)
	: GameEntity(x,y)
	, maxHp(maxHp)
{
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


void Character::Die()
{
	//find a way to invoke event
	//system("cls");
	//std::cout << "Your HP reached 0! Game over." << std::endl;
	//exit(1);
}