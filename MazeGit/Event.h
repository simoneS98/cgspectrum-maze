#pragma once
#include <stdlib.h>
#include <iostream>
#include "Game.h"
#include "StateMachineExampleGame.h"

class Event
{
protected:
	bool isDone;
	void (*m_pCallback)(void);
	//Event(void (*callback)(void));
public:
	Event();
	~Event();
	bool IsDone() const { return isDone; }
	virtual void Activate(StateMachineExampleGame* gsm) = 0;
};

