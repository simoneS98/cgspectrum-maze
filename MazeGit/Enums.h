#pragma once
enum class RoomContent
{
	PLAYER = 64,

	WALL = 219,
	KEY = 43,
	DOOR = 68,
	EMPTY = 32,

	WALL_CONVERTED = 124,

	//hazards
	SPIKES = 88
};

enum class RoomColor
{
	DOOR_OPEN = 10,
	DOOR_CLOSED = 12,
	DEFAULT = 7,
	HAZARD = 13
};