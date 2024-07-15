#include "RoomFactory.h"
#include <stdexcept>

Room* RoomFactory::make(Sprite type)
{
	Room* instance = nullptr;

	/*
	switch (type)
	{
		//case RoomType::WALL:
		case Sprite::KEY:
		case Sprite::DOOR:
		case Sprite::EMPTY:
		case Sprite::EXIT:
			instance = new Room(type);
			break;
		case Sprite::WALL_CONVERTED:
			instance = new Room(Sprite::WALL);
			break;
		case Sprite::SPIKES:
			instance = new HazardRoom(type,Color::HAZARD, 1);
			break;
		default:
			instance = new Room(Sprite::EMPTY);
			//throw std::invalid_argument("RoomType not defined");
			break;
	}
	*/

	return instance;
}