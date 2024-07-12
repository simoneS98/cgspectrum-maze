#pragma once
#include <string>
#include <Enums.h>
#include <Structs.h>
#include <Room.h>

constexpr int cMaxWidth = 40;
constexpr int cMaxHeight = 20;

class RoomEditor
{
	
public:
	Level* GetLevelDimensions();
	void DisplayLevel(Level level, int cursorX = -1, int cursorY = -1);
	int GetIndexFromXY(int x, int y, int width);
	void DisplayLeftBorder();
	void DisplayRightBorder();
	void DisplayHorizontalBorder(int width);
	void DisplayVerticalBorder();
	void DisplayRoom(char* pLevel, int index);
	bool FillRoom(Level* level, Cursor* cursor);
	void DisplayRoomChoices();
	int GetRoomChoice(Input input);
	bool PlaceDoors(Level* level);
	void SaveLevel(Level* level);
	void SaveRoom();
	bool EditRoom(char* editableArea, Cursor* cursor, int editableAreaWidth, int editableAreaHeight);
	void Display(char* editableArea, Cursor* cursor);
	void DisplayLegend();
private:
	void PlaceAt(RoomContent content, int x, int y);
	bool SaveRoom(std::string name);
};

