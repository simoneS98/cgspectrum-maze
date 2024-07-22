#include "EventManager.h"

EventManager* EventManager::instance = nullptr;

EventManager* EventManager::GetInstance()
{
	if (instance == nullptr)
		instance = new EventManager();
	return instance;
}

void EventManager::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

void EventManager::Add(Event* e)
{
	eventsQueue.push_back(e);
}

void EventManager::ActivateEvents()
{
	for (auto event = eventsQueue.begin(); event != eventsQueue.end(); ++event)
	{
		(*event)->Activate();
		if ((*event)->IsDone())
		{
			eventsQueue.erase(event);
			delete* event;
			(*event) = nullptr;
		}
			
	}
}
