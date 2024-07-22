#include "PlayerDeathEvent.h"
#include <stdlib.h>

PlayerDeathEvent::PlayerDeathEvent()
	: Event()
{
}

bool PlayerDeathEvent::Activate()
{
	exit(1);
	return true;
}
