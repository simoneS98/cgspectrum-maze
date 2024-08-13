#include "EventManager.h"

EventManager* EventManager::instance = nullptr;

EventManager::EventManager()
	: m_isLocked(false)
{
}

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
	if (m_isLocked)
		return;

	// place debug here, check contents of eventsQueue and eventsQueue.begin()
	// should I use a copy of eventsQueue?
	if (eventsQueue.empty())
		return;

	m_isLocked = true;
	int i = 0;

	std::vector<Event*> tmp{ eventsQueue };
	for (auto event = tmp.begin(); event != tmp.end(); ++event)
	{
		i++;
		if (!(*event)->IsDone())
		{
			(*event)->Activate(gameStateMachine);
		}
	}

	// removed to avoid nullptrs...for now
	
	eventsQueue.erase(
	std::remove_if(
		eventsQueue.begin(),
		eventsQueue.end(),
		[](Event* e) { return e->IsDone(); }
	),
	eventsQueue.end()
	);
	

	

	
	m_isLocked = false;

}


