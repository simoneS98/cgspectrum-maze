#include "RoomEditor.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>  
#include <Door.h>
#include <Constants.h>

using namespace std;

int main()
{
    //init level
    RoomEditor r = RoomEditor();
    Cursor* cursor = new Cursor();
    char* editableArea = new char[cMaxRoomWidth * cMaxRoomHeight];

    for (int i = 0; i < cMaxRoomWidth * cMaxRoomHeight; i++)
    {
        editableArea[i] = (char)Sprite::EMPTY;
    }

    bool doneEditing = false;

    while (!doneEditing)
    {
        r.Display(editableArea, cursor);
        r.DisplayLegend();
        doneEditing = r.EditRoom(editableArea, cursor, cMaxRoomWidth, cMaxRoomHeight);
    }
    
    r.Save(editableArea);



    /*
    Level* level = r.GetLevelDimensions();
    Cursor* cursor = new Cursor;

    int levelSize = level->width * level->height;

    level->map = new char[levelSize];

    for (int i = 0; i < levelSize; i++)
    {
        level->map[i] = (char)RoomContent::EMPTY;
    }

    bool doneEditing = false;

    // fill room
    while (!doneEditing)
    {
        system("cls");
        r.DisplayRoomChoices();
        r.DisplayLevel(*level, cursor->x, cursor->y);
        doneEditing = r.FillRoom(level, cursor);
    }

    doneEditing = true;

    // create doors
   

    system("cls");

    r.SaveLevel(level);

    delete level;
    level = nullptr;
    */
    
}



Level* RoomEditor::GetLevelDimensions()
{
    Level* level = new Level;

    cout << "Enter the width of your level: " << endl;
    cin >> level->width;

    cout << "Enter the height of your level: " << endl;
    cin >> level->height;

    return level;
}

int RoomEditor::GetIndexFromXY(int x, int y, int width)
{
    return x * width + y;
}

void RoomEditor::DisplayLeftBorder()
{
    DisplayVerticalBorder();
}

void RoomEditor::DisplayRightBorder()
{
    DisplayVerticalBorder();
    cout << endl;
}

void RoomEditor::DisplayVerticalBorder()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (int)Color::PERIMETER);
    cout << (char)Sprite::PERIMETER;
    SetConsoleTextAttribute(hConsole, (int)Color::DEFAULT);
}

void RoomEditor::DisplayHorizontalBorder(int width)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (int)Color::PERIMETER);

    for (int i = -1; i < width + 1; i++)
    {
        cout << (char)Sprite::PERIMETER;
    }

    cout << endl;

    SetConsoleTextAttribute(hConsole, (int)Color::DEFAULT);
}

void RoomEditor::DisplayRoom(char* pLevel, int index)
{
    cout << pLevel[index];
}

bool RoomEditor::FillRoom(Level* level, Cursor* cursor)
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
        if (intInput == cInputEsc)
        {
            return true;
        }
        else if (intInput == cInputBackSpace)
        {
            // ignore
        }
        else
        {
            int index = GetIndexFromXY(newCursorX, newCursorY, level->width);

            //level->map[index] = GetRoomChoice(Input(intInput));
        }
    }

    return false;
}

bool RoomEditor::IsTileValid(char input)
{
    return input == (char)Editor::CORNER
        || input == (char)Editor::WALL_V
        || input == (char)Editor::WALL_H
        || input == (char)Editor::KEY_GREEN
        || input == (char)Editor::KEY_RED
        || input == (char)Editor::KEY_BLUE
        || input == (char)Editor::DOOR_RED
        || input == (char)Editor::DOOR_GREEN
        || input == (char)Editor::DOOR_BLUE
        || input == (char)Editor::MONEY
        || input == (char)Editor::EXIT
        || input == (char)Editor::PLAYER
        || input == (char)Editor::ENEMY
        || input == (char)Editor::ENEMY_H
        || input == (char)Editor::ENEMY_V
        || input == (char)Editor::EMPTY
        || ( input >= '0' && input <= '9' );
}

void RoomEditor::SaveLevel(Level* level)
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
        levelFile << /*"width=" <<*/ cMaxRoomWidth << endl;
        levelFile << /*"height=" <<*/ cMaxRoomHeight << endl;
        //levelFile << "level=";
        for (int i = 0; i < cMaxRoomWidth * cMaxRoomHeight; i++)
        {
            levelFile << (level->map[i] == (char)Sprite::WALL ? (char)Sprite::WALL_CONVERTED : level->map[i]);
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

void RoomEditor::Save(char* editableArea)
{
    cout << "To which level does this room belong to? (insert directory name): ";
    string levelName;
    cin >> levelName;

    levelName.insert(0, "../levels/");

    string cmd = "mkdir";

    cmd.append(" \"").append(levelName).append("\"");

    cout << "cmd" << cmd << endl;

    system(cmd.c_str());

    cout << "Pick a name for your room file (only integers from 0 to 9 are allowed: eg. 1 or 5): ";
    string roomName;
    cin >> roomName;
    
    string fileName = levelName.append("/").append(roomName).append(".room");


    //prepends parent dir to filename
    //fileName.insert(0, "../");

    cout << fileName;

    ofstream levelFile;
    levelFile.open(fileName);

    if (!levelFile)
    {
        cout << "Opening file failed!" << endl;
    }
    else
    {
        levelFile <<  cMaxRoomWidth << endl;
        levelFile <<  cMaxRoomHeight << endl;
        for (int i = 0; i < cMaxRoomWidth * cMaxRoomHeight; i++)
        {
            levelFile << (editableArea[i] == (char)Sprite::WALL ? (char)Sprite::WALL_CONVERTED : editableArea[i]);
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

bool RoomEditor::EditRoom(char* editableArea, Cursor* cursor, int editableAreaWidth, int editableAreaHeight)
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
        else if (newCursorX == editableAreaHeight)
            newCursorX = editableAreaHeight - 1;
        else if (newCursorY < 0)
            newCursorY = 0;
        else if (newCursorY == editableAreaWidth)
            newCursorY = editableAreaWidth - 1;

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
            int index = GetIndexFromXY(newCursorX, newCursorY, editableAreaWidth);

            //Input in = Input(intInput);
            //string filename;

            if(IsTileValid((char)intInput))
                editableArea[index] = (char)intInput;
            else
                editableArea[index] = (char)Editor::EMPTY;
        }
    }

    return false;
}

void RoomEditor::Display(char* editableArea, Cursor* cursor)
{
    DisplayHorizontalBorder(cMaxRoomWidth);

    for (int x = 0; x < cMaxRoomHeight; x++)
    {
        DisplayLeftBorder();
        for (int y = 0; y < cMaxRoomWidth; y++)
        {
            if (x == cursor->x && y == cursor->y)
                cout << "P";
            else
                cout << editableArea[GetIndexFromXY(x,y, cMaxRoomWidth)];
        }
        
        DisplayRightBorder();
    }

    DisplayHorizontalBorder(cMaxRoomWidth);

}

void RoomEditor::DisplayLegend()
{
    cout << "Arrows to move cursor" << endl;
    cout << "ESC to finish editing" << endl;
    cout << "+ | - for walls" << endl;
    cout << "@ for player start" << endl;
    cout << "r g b for key" << endl;
    cout << "R G B for door" << endl;
    cout << "$ for money" << endl;
    cout << "v for vertical moving enemy" << endl;
    cout << "h for horizontal moving enemy" << endl;
    cout << "e for non-moving enemy" << endl;
    cout << "X for end" << endl;
}
