#include "RoomFactory.h"
#include <stdexcept>

Room* RoomFactory::make(RoomContent type)
{
	Room* instance;

	switch (type)
	{
		//case RoomType::WALL:
		case RoomContent::KEY:
		case RoomContent::DOOR:
		case RoomContent::EMPTY:
			instance = new Room(type);
			break;
		case RoomContent::WALL_CONVERTED:
			instance = new Room(RoomContent::WALL);
			break;
		case RoomContent::SPIKES:
			instance = new HazardRoom(type,RoomColor::HAZARD, 1);
			break;
		default:
			instance = new Room(RoomContent::EMPTY);
			//throw std::invalid_argument("RoomType not defined");
			break;
	}

	return instance;
}