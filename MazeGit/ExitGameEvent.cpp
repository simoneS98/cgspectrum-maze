#include "ExitGameEvent.h"

ExitGameEvent::ExitGameEvent(const std::string exitCause)
	: m_message(exitCause)
{
}

void ExitGameEvent::Activate(StateMachineExampleGame* gsm)
{
	gsm->Quit(m_message);
	isDone = true;
}
