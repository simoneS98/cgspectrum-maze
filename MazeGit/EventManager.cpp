#include "EventManager.h"
#include "Game.h"

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

void EventManager::ActivateEvents(Game* game)
{
	if (eventsQueue.empty())
		return;
	for (auto event = eventsQueue.begin(); event != eventsQueue.end(); ++event)
	{
		// brrr
		if(!(*event)->IsDone())
			(*event)->Activate(game);
		/*
				if ((*event)->IsDone())
		{
			//eventsQueue.erase(event);
			delete (*event);
			//(*event) = nullptr;
		}
		*/

			
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
/*
void EventManager::ActivateEvents(GameStateMachine* gameStateMachine)
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
*/

