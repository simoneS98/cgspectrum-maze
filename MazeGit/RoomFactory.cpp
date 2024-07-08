#include "RoomFactory.h"
#include <stdexcept>

Room* RoomFactory::make(RoomType type)
{
	Room* instance;

	switch (type)
	{
		//case RoomType::WALL:
		case RoomType::KEY:
		case RoomType::DOOR:
		case RoomType::EMPTY:
			instance = new Room(type);
			break;
		case RoomType::WALL_CONVERTED:
			instance = new Room(RoomType::WALL);
			break;
		case RoomType::SPIKES:
			instance = new HazardRoom(type,RoomColor::HAZARD, 1);
			break;
		default:
			instance = new Room(RoomType::EMPTY);
			//throw std::invalid_argument("RoomType not defined");
			break;
	}

	return instance;
}