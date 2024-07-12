#pragma once
#include "Player.h"
#include "Enums.h"
#include "string"

// TODO: room of varying sizes
class Room
{
	RoomContent content;
	RoomColor color;
	bool isAccessible;

	public:
		// Constructors
		Room();

		Room(RoomContent content);

		Room(RoomContent content, RoomColor color);

		void Display();

		bool IsAccessibleBy(Player *p) const;
		bool IsExit() const;

		// used to change room at runtime
		void AlterRoom(RoomContent content, RoomColor color);
		virtual void OnEnter(Player* p);
		
	private:
		void PlaySoundtrack();
		
};

class HazardRoom : public Room
{
	public:
		HazardRoom(RoomContent content, int damage);
		HazardRoom(RoomContent content, RoomColor color,int damage);

		void OnEnter(Player* p) override;

	private:
		int damage;
};