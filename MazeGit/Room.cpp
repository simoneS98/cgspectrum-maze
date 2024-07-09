#include "Room.h"
#include <iostream>
#include <windows.h>  

Room::Room() : Room(RoomContent::EMPTY, RoomColor::DEFAULT){}

Room::Room(RoomContent content) : Room(content, RoomColor::DEFAULT){}

Room::Room(RoomContent content, RoomColor color)
{
	this->content = content;
	this->color = color;
	isAccessible = true;
}

void Room::Display()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (int)color);

	std::cout << (char)content;
}

void Room::AlterRoom(RoomContent type, RoomColor color)
{
	this->color = color;
	this->content = type;
}

bool Room::IsAccessibleBy(Player* p) const
{
	bool isObstacle = (content == RoomContent::WALL);
	bool isLocked = (content == RoomContent::DOOR && p->GetNumKeys() == 0);

	return !(isObstacle || isLocked);
}

void Room::OnEnter(Player* p)
{
	// no need in using a function which only works on specific rooms...
	// TODO: switch content to Object
	switch (content)
	{
	case(RoomContent::KEY):
		p->PickupKey();
		content = RoomContent::EMPTY;
		break;
	case(RoomContent::DOOR):
		if(p->UseKey())
			content = RoomContent::EMPTY;
		break;
	}
	//playsoundtrack
}

void Room::PlaySoundtrack()
{
	Beep(1568, 200);
	Beep(1568, 200);
	Beep(1568, 200);
	Beep(1245, 1000);
	Beep(1397, 200);
	Beep(1397, 200);
	Beep(1397, 200);
	Beep(1397, 200);
	Beep(1157, 1000);
}


void HazardRoom::OnEnter(Player* p)
{
	p->TakeDamage(damage);
	__super::OnEnter(p);

}

HazardRoom::HazardRoom(RoomContent type, int damage): Room(type)
{
	this->damage = damage;
}

HazardRoom::HazardRoom(RoomContent type, RoomColor color, int damage) : Room(type,color)
{
	this->damage = damage;
}
