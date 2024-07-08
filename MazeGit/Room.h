#pragma once
#include "Player.h"
#include "Enums.h"
#include "string"

class Room
{
	public:
		Room();

		Room(RoomType type);

		Room(RoomType type, RoomColor color);

		void Display();

		bool IsAccessible() const;

		// used to change room at runtime
		void AlterRoom(RoomType type, RoomColor color);
		virtual void OnEnter(Player* p);
		
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

		void OnEnter(Player* p);

	private:
		int damage;
};