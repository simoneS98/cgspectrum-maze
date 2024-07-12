#include "RoomEditor.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>  
#include <Door.h>

using namespace std;

int main()
{
    //init level
    RoomEditor r = RoomEditor();
    Cursor* cursor = new Cursor();
    char* editableArea = new char[cMaxWidth * cMaxHeight];

    for (int i = 0; i < cMaxWidth * cMaxHeight; i++)
    {
        editableArea[i] = (char)RoomContent::EMPTY;
    }

    bool doneEditing = false;

    while (!doneEditing)
    {
        r.DisplayRoomChoices();
        r.Display(editableArea, cursor);
        doneEditing = r.EditRoom(editableArea, cursor, cMaxWidth, cMaxHeight);
    }
    
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
    SetConsoleTextAttribute(hConsole, (int)RoomColor::PERIMETER);
    cout << (char)RoomContent::PERIMETER;
    SetConsoleTextAttribute(hConsole, (int)RoomColor::DEFAULT);
}

void RoomEditor::DisplayHorizontalBorder(int width)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (int)RoomColor::PERIMETER);

    for (int i = -1; i < width + 1; i++)
    {
        cout << (char)RoomContent::PERIMETER;
    }

    cout << endl;

    SetConsoleTextAttribute(hConsole, (int)RoomColor::DEFAULT);
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

void RoomEditor::DisplayRoomChoices()
{
    //TODO: add n blocks left
    cout << "\t" << (int)Input::WALL - 48 << ": Block" << endl;
    cout << "\t" << (int)Input::SPIKES - 48 << ": Spikes" << endl;
    cout << "\t" << (int)Input::KEY - 48 << ": Key" << endl;
    cout << "\t" << (int)Input::DOOR - 48 << ": Door" << endl;
}

int RoomEditor::GetRoomChoice(Input input)
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
        // TODO: where does this door lead to?
        roomChoice = (int)RoomContent::DOOR;
        break;
        break;
    default:
        roomChoice = (char)RoomContent::EMPTY;
        break;
    }

    return roomChoice;

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

            Input in = Input(intInput);
            string filename;

            editableArea[index] = GetRoomChoice(Input(intInput));

            if (in == Input::DOOR)
            {
                cout << "What room does this door lead to? (insert room filename)";

                cin >> filename;

                Door* d = new Door(1, 2);
            }
        }
    }

    return false;
}

void RoomEditor::Display(char* editableArea, Cursor* cursor)
{
    DisplayHorizontalBorder(cMaxWidth);

    for (int x = 0; x < cMaxHeight; x++)
    {
        DisplayLeftBorder();
        for (int y = 0; y < cMaxWidth; y++)
        {
            if (x == cursor->x && y == cursor->y)
                cout << "P";
            else
                cout << editableArea[GetIndexFromXY(x,y,cMaxWidth)];
        }
        
        DisplayRightBorder();
    }

    DisplayHorizontalBorder(cMaxWidth);

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
