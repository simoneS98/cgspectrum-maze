#include "ShowLeaderboardEvent.h"
#include "StateMachineExampleGame.h"

ShowLeaderboardEvent::ShowLeaderboardEvent()
{
}

void ShowLeaderboardEvent::Activate(StateMachineExampleGame* gsm)
{
    gsm->ShowScores();
    isDone = true;
}
