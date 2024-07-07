#include "Room.h"
#include <iostream>
#include <windows.h>  

Room::Room() : Room(RoomType::EMPTY, RoomColor::DEFAULT){}

Room::Room(RoomType type) : Room(type, RoomColor::DEFAULT){}

Room::Room(RoomType type, RoomColor color)
{
	this->type = type;
	this->color = color;
	isAccessible = true;
}

void Room::Display()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (int)color);

	std::cout << (char)type;
}

void Room::AlterRoom(RoomType type, RoomColor color)
{
	this->color = color;
	this->type = type;
}

bool Room::Enter(Player* p)
{
	//do nothing
	return isAccessible;
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


bool HazardRoom::Enter(Player* p)
{
	p->TakeDamage(damage);
	return Room::Enter(p);
}

HazardRoom::HazardRoom(RoomType type, int damage): Room(type)
{
	this->damage = damage;
}

HazardRoom::HazardRoom(RoomType type, RoomColor color, int damage) : Room(type,color)
{
	this->damage = damage;
}