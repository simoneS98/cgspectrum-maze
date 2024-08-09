#pragma once
#include <vector>
#include "Event.h"

class GameStateMachine;

class EventManager
{
private:
	EventManager();
	static EventManager* instance;
	std::vector<Event*> eventsQueue;
	void Remove();
	// used to hopefully avoid race conditions in singleton
	bool m_isLocked;
public:
	static EventManager* GetInstance();
	static void DestroyInstance();
	void Add(Event* e);
	void ActivateEvents(StateMachineExampleGame* gameState);

};

