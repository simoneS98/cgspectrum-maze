#pragma once
#include "Room.h"
#include "Enums.h"

class RoomFactory
{
	public:
		static Room make(RoomType type);
};
