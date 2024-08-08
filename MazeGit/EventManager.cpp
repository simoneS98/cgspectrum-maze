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

void EventManager::ActivateEvents(StateMachineExampleGame* gameStateMachine)
{
	if (eventsQueue.empty())
		return;

	for (auto event = eventsQueue.begin(); event != eventsQueue.end(); ++event)
	{
		// brrr
		if (!(*event)->IsDone())
			(*event)->Activate(gameStateMachine);

	}

	
	eventsQueue.erase(
	std::remove_if(
		eventsQueue.begin(),
		eventsQueue.end(),
		[](Event* e) { return e->IsDone(); }
	),
	eventsQueue.end()
	);
	

}


