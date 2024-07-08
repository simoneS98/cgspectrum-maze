// LevelEditor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <Structs.h>
#include "Enums.h"

using namespace std;

Level* GetLevelDimensions();
void DisplayLevel(Level level, int cursorX = -1, int cursorY = -1);
int GetIndexFromXY(int x, int y, int width);
void DisplayTopBorder(int width);
void DisplayBottomBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();
void DisplayHorizontalBorder(int width);
void DisplayVerticalBorder();
void DisplayRoom(char* pLevel, int index);
bool EditLevel(Level* level, Cursor* cursor);
void DisplayRoomChoices();
int GetRoomChoice(Input input);
void SaveLevel(Level* level);



int main()
{
    //init level
    Level* level = GetLevelDimensions();
    Cursor* cursor = new Cursor;

    int levelSize = level->width * level->height;

    level->map = new char[levelSize];

    for (int i = 0; i < levelSize; i++)
    {
        level->map[i] = (char)RoomContent::EMPTY;
    }

    bool doneEditing = false;

    while (!doneEditing)
    {
        system("cls");
        DisplayRoomChoices();
        DisplayLevel(*level, cursor->x, cursor->y);
        doneEditing = EditLevel(level, cursor);
    }

    system("cls");

    SaveLevel(level);

    delete level;
    level = nullptr;
}


Level* GetLevelDimensions()
{
    Level* level = new Level;

    cout << "Enter the width of your level: " << endl;
    cin >> level->width;

    cout << "Enter the height of your level: " << endl;
    cin >> level->height;

    return level;
}


void DisplayLevel(Level level, int cursorX, int cursorY)
{
    DisplayTopBorder(level.width);

    for (int x = 0; x < level.height; x++)
    {
        DisplayLeftBorder();
        for (int y = 0; y < level.width; y++)
        {
            if (cursorX == x && cursorY == y)
            {
                cout << (char)RoomContent::CURSOR;
            }
            else
            {
                int index = GetIndexFromXY(x, y, level.width);
                DisplayRoom(level.map, index);
            }
        }
        DisplayRightBorder();
    }

    DisplayBottomBorder(level.width);
}

int GetIndexFromXY(int x, int y, int width)
{
    return x * width + y;
}

void DisplayTopBorder(int width)
{
    cout << (char)RoomContent::WALL;

    DisplayHorizontalBorder(width);

    cout << (char)RoomContent::WALL << endl;
}

void DisplayBottomBorder(int width)
{
    cout << (char)RoomContent::WALL;

    DisplayHorizontalBorder(width);

    cout << (char)RoomContent::WALL << endl;
}

void DisplayLeftBorder()
{
    DisplayVerticalBorder();
}

void DisplayRightBorder()
{
    DisplayVerticalBorder();
    cout << endl;
}

void DisplayVerticalBorder()
{
    cout << (char)RoomContent::WALL;
}

void DisplayHorizontalBorder(int width)
{
    for (int i = 0; i < width; i++)
    {
        cout << (char)RoomContent::WALL;
    } 
}

void DisplayRoom(char* pLevel, int index)
{
    cout << pLevel[index];
}

bool EditLevel(Level* level, Cursor* cursor)
{
    int newCursorX = cursor->x;
    int newCursorY = cursor->y;

    int intInput = _getch();
    //int intInput = GetRoomChoice();

    //check if an arrow key was pressed
    if (intInput == (int)Input::ARROW_IN)
    {
        //read actual arrow value
        int arrowInput = _getch();
      
        switch (arrowInput)
        {
            case (int)Input::ARROW_LEFT:
                newCursorY--;
                break;
            case (int)Input::ARROW_RIGHT:
                newCursorY++;
                break;
            case (int)Input::ARROW_UP:
                newCursorX--;
                break;
            case (int)Input::ARROW_DOWN:
                newCursorX++;
                break;
        }

        if (newCursorX < 0)
            newCursorX = 0;
        else if (newCursorX == level->height)
            newCursorX = level->height - 1;
        else if (newCursorY < 0)
            newCursorY = 0;
        else if (newCursorY == level->width)
            newCursorY = level->width - 1;

        cursor->x = newCursorX;
        cursor->y = newCursorY;
    }
    else
    {
        if (intInput == (int)Input::ESC)
        {
            return true;
        }
        else
        {
            int index = GetIndexFromXY(newCursorX, newCursorY, level->width);

            level->map[index] = GetRoomChoice(Input(intInput));
        }
    }

    return false;
}

void DisplayRoomChoices()
{
    //TODO: add n blocks left
    cout << "\t" << (int)Input::WALL - 48 << ": Block" << endl;
    cout << "\t" << (int)Input::SPIKES - 48 <<": Spikes" << endl;
    cout << "\t" << (int)Input::KEY - 48 << ": Key" << endl;
    cout << "\t" << (int)Input::DOOR - 48 << ": Door" << endl;
}

int GetRoomChoice(Input input)
{
    int roomChoice;

    switch (input)
    {
        case Input::WALL:
            roomChoice = (int)RoomContent::WALL;
            break;
        case Input::SPIKES:
            roomChoice = (int)RoomContent::SPIKES;
            break;
        case Input::KEY:
            roomChoice = (int)RoomContent::KEY;
            break;
        case Input::DOOR:
            roomChoice = (int)RoomContent::DOOR;
            break;
            break;
        default:
            roomChoice = (char)RoomContent::EMPTY;
            break;
    }

    return roomChoice;

}

void SaveLevel(Level* level)
{
    cout << "Pick a name for your level file (eg: Level1.txt): ";
    string levelName;
    cin >> levelName;

    //prepends parent dir to filename
    levelName.insert(0, "../");

    ofstream levelFile;
    levelFile.open(levelName);

    if (!levelFile)
    {
        cout << "Opening file failed!" << endl;
    }
    else
    {
        levelFile << /*"width=" <<*/ level->width << endl;
        levelFile << /*"height=" <<*/ level->height << endl;
        //levelFile << "level=";
        for (int i = 0; i < level->width * level->height; i++)
        {
            levelFile << (level->map[i] == (char)RoomContent::WALL ? (char)RoomContent::WALL_CONVERTED : level->map[i]);
        }
        levelFile << endl;
        //levelFile.write(level->map, level->width * level->height); //width * height : streamsize
        if (!levelFile)
        {
            cout << "Write failed!" << endl;
        }
        levelFile.close();
    }
}
