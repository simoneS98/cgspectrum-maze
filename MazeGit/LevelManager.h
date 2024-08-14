#pragma once
#include <string>
#include "Room.h"

class LevelManager
{
private:
	LevelManager() {}
	static LevelManager* instance;
	std::string m_levelName;
	Room* m_pRoomBefore;
	Room* m_pCurrentRoom;
	void Remove();
public:
	static LevelManager* GetInstance();
	static void DestroyInstance();
	void SaveRoomState(bool createTmpFile);
	bool Load(std::string roomName);
	void Clear()
	{
		// useless
		m_levelName = "";

		delete m_pCurrentRoom;
		m_pCurrentRoom = nullptr;

		// place file deletion here?
	}
	//static void SetLevelName(std::string levelName) { instance->SetLevelName(levelName);}
	void SetLevelName(std::string levelName) { this->m_levelName = levelName; }
	std::string GetLevelName() { 
		if (m_pCurrentRoom == nullptr)
			return "";
		return this->m_levelName; 
	}
	Room* GetCurrentRoom(){	return m_pCurrentRoom;	}
};

