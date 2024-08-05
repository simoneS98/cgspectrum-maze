#pragma once
#include "GameState.h"

class GameStateMachine
{
public:
	virtual ~GameStateMachine() = default;

	virtual bool Init() = 0;
	virtual bool UpdateCurrentState(bool processInput = true) = 0;
	virtual bool DrawCurrentState() = 0;
	virtual void ChangeState(GameState* pNextState) = 0;
	virtual bool Cleanup() = 0;
};

