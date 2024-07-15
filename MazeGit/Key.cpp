#include <iostream>
#include "windows.h"

#include "Key.h"

void Key::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, color);

	std::cout << keySprite;

	SetConsoleTextAttribute(console, cDefaultColor);
}
