#include "RoomFactory.h"
#include <stdexcept>

Room RoomFactory::make(RoomType type)
{
	Room instance;

	switch (type)
	{
		case RoomType::WALL:
		case RoomType::KEY:
		case RoomType::DOOR:
		case RoomType::EMPTY:
			instance = Room(type);
			break;
		case RoomType::SPIKES:
			instance = HazardRoom(type,1);
			break;
		default:
			instance = Room(RoomType::EMPTY);
			//throw std::invalid_argument("RoomType not defined");
			break;
	}

	return instance;
}