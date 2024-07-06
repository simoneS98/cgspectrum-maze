#pragma once
#include "Player.h"
#include "Enums.h"

class Room
{
	public:
		Room();

		Room(RoomType type);

		Room(RoomType type, RoomColor color);

		void Display();

		// used to change room at runtime
		void AlterRoom(RoomType type, RoomColor color);
		bool Enter(Player* p); 
	private:
		RoomType type;
		RoomColor color;
		bool isAccessible;

		void PlaySoundtrack();
};

class HazardRoom : public Room
{
	public:
		HazardRoom(RoomType type, int damage);
		HazardRoom(RoomType type, RoomColor color,int damage);
		int Damage();
		bool Enter(Player* p);
	private:
		int damage;
};