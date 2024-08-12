#include "LoadLevelScoresEvent.h"

LoadLevelScoresEvent::LoadLevelScoresEvent(std::string levelName)
	: m_levelName(levelName)
{
}
void LoadLevelScoresEvent::Activate(StateMachineExampleGame* gsm)
{
	gsm->ShowScores(m_levelName.c_str());
}
