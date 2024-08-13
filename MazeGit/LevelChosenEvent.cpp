#include "LevelChosenEvent.h"

LevelChosenEvent::LevelChosenEvent(std::string levelName)
	: m_levelName(levelName)
{
}

void LevelChosenEvent::Activate(StateMachineExampleGame* gsm)
{
	gsm->ChooseLevel(m_levelName);
	isDone = true;
}
