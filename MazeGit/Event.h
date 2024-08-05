#pragma once
#include <stdlib.h>
#include <iostream>
#include "Game.h"
class Event
{
protected:
	bool isDone;
	void (*m_pCallback)(void);
	Event(void (*callback)(void));
public:
	Event();
	~Event();
	bool IsDone() const { return isDone; }
	virtual bool Activate(Game* game) = 0;
	//virtual bool Activate() = 0;
};

