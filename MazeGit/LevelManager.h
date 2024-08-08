#pragma once
#include <string>

class Room;

class LevelManager
{
private:
	LevelManager() {}
	static LevelManager* instance;
	std::string levelName;
	Room* m_pRoomBefore;
	Room* currentRoom;
	void Remove();
public:
	static LevelManager* GetInstance();
	static void DestroyInstance();
	void Save();
	bool Load(std::string roomName);
	//static void SetLevelName(std::string levelName) { instance->SetLevelName(levelName);}
	void SetLevelName(std::string levelName) { this->levelName = levelName; }
	std::string GetLevelName() { 
		if (currentRoom)
			return "";
		return this->levelName; 
	}
	Room* GetCurrentRoom(){	return currentRoom;	}
	/*
	Room** GetMap()
	{
		return map;
	}*/

};

