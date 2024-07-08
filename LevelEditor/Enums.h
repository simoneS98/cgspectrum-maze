#pragma once
enum class RoomContent
{
	CURSOR = 95,

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
	DEFAULT = 7
};

enum class Input
{
	ARROW_IN = 0xE0, //or 224

	//key scan codes https://learn.microsoft.com/it-it/previous-versions/visualstudio/visual-studio-6.0/aa299374(v=vs.60)
	ARROW_LEFT = 75,
	ARROW_RIGHT = 77,
	ARROW_UP = 72,
	ARROW_DOWN = 80,

	ESC = 27,

	WALL = 49,
	SPIKES = 50,
	KEY = 51,
	DOOR = 52
};