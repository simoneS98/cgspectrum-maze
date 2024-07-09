#pragma once
#include <string>
#include "Room.h"

class Level
{
    public:
        // Constructors
        Level();
        Level(Room** map, int width, int height);

        // Getters
        int GetWidth();
        int GetHeight();
        int GetSize();
        Room* GetRoom(int x, int y);
        Room** GetMap();

        bool Load(std::string filename);
        void DisplayLeftBorder();
        void DisplayRightBorder();
        void DisplayHorizontalBorder();
        void DisplayVerticalBorder();

        // Setters
        //void SetWidth(int width);
        //void SetHeight(int width);

    private:
        int width = 0;
        int height = 0;
        Room** map = nullptr;

        int GetIndexFromXY(int x, int y);
};