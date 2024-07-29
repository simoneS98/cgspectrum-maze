#include "Character.h"
#include "Room.h"
Character::Character(int x, int y, Room* pRoom, int maxHp)
	: GameEntity(x,y,pRoom)
	, maxHp(maxHp)
	, pCurrentKey(nullptr)
{
	hp = maxHp;
	type = EntityType::ACTIVE;
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
	if (pCurrentKey == nullptr)
	{
		pCurrentKey = (Key*)key;
		pRoom->RemoveFrom(key,key->GetPosition());
	}

	return true;
}


void Character::Die()
{
	//find a way to invoke event
	//system("cls");
	//std::cout << "Your HP reached 0! Game over." << std::endl;
	//exit(1);
}