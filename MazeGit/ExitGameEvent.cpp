#include "ExitGameEvent.h"

ExitGameEvent::ExitGameEvent(const std::string exitCause)
	: m_message(exitCause)
{
	isDone = true;
}

void ExitGameEvent::Activate(StateMachineExampleGame* gsm)
{
	std::cout << "ATTIVO EVENT CON MSG " << m_message << std::endl;
	
	gsm->Quit(m_message);
	
}
