#pragma once
#ifdef _DEBUG

class DebugManager
{

private:
	static DebugManager* instance;
public:
	static DebugManager* GetInstance();
	bool IsPlayerInvicible();
};


#endif // DEBUG
