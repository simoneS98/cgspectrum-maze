#include "DebugManager.h"
DebugManager* DebugManager::instance = nullptr;

DebugManager* DebugManager::GetInstance()
{
	if (instance == nullptr)
		instance = new DebugManager();
	return instance;
}

bool DebugManager::IsPlayerInvicible()
{
	return true;
}
