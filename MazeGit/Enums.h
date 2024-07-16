#pragma once
enum class Editor : char
{
	EMPTY = ' ',
	CORNER = '+',
	WALL_H = '-',
	WALL_V = '|',
	ENEMY = 'e',
	ENEMY_H = 'h',
	ENEMY_V = 'v',
	KEY_RED = 'r',
	KEY_GREEN = 'g',
	KEY_BLUE = 'b',
	DOOR_RED = 'R',
	DOOR_GREEN = 'G',
	DOOR_BLUE = 'B',
	PLAYER = '@',
	MONEY = '$',
	EXIT = 'X'
};
enum class Sprite
{
	PLAYER = 64,

	WALL = 219,
	KEY = 43,
	MONEY = 36,
	DOOR = 88, // X
	EMPTY = 32,
	EXIT = 79,

	WALL_CONVERTED = 124,
	CURSOR = 95,
	PERIMETER = 176,

	// hazards
	SPIKES = 88,

	// enemies
	ENEMY = 153
};

enum class Color
{
	DOOR_OPEN = 10,
	DOOR_CLOSED = 12,
	DEFAULT = 7,
	HAZARD = 13,
	PERIMETER = 8,
	GREEN_MONEY = 2,
	RED = 12,
	GREEN = 10,
	BLUE = 9
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
	BACK = 8,

	WALL = 49,
	SPIKES = 50,
	KEY = 51,
	DOOR = 52
};