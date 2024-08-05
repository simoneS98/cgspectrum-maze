#pragma once
#include <vector>
#include "Event.h"

class GameStateMachine;

class EventManager
{
private:
	EventManager() {}
	static EventManager* instance;
	std::vector<Event*> eventsQueue;
	void Remove();
public:
	static EventManager* GetInstance();
	static void DestroyInstance();
	void Add(Event* e);
	void ActivateEvents(Game* game);
	void ActivateEvents(GameStateMachine* gameState);

};

