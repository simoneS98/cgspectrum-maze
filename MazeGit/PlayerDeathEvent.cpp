#include "PlayerDeathEvent.h"


PlayerDeathEvent::PlayerDeathEvent()
	: Event()
{
}

void PlayerDeathEvent::Activate(StateMachineExampleGame* gsm)
{
	gsm->Quit("No more lives left! GAME OVER");
	isDone = true;
}
