#pragma once
#include <string>
#include "Room.h"
#include <vector>

// TODO: everything which is printed is related to the CURRENT room
class Level
{
    public:
        // Constructors
        Level();
        Level(Room** map, int width, int height);

        // Destructors
        ~Level();

        // Getters
        int GetWidth();
        int GetHeight();
        int GetSize();
        Room* GetRoom(int x, int y);
        Room* GetCurrentRoom();
        Room** GetMap();

        bool Load(std::string levelName, std::string roomName = "0");
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
        std::vector<GameEntity*> pEntities;
        Room** map = nullptr;
        Room* currentRoom = nullptr;

        int GetIndexFromXY(int x, int y);
};