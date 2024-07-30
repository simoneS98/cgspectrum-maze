#pragma once
#include <stdlib.h>
#include <iostream>
#include "Game.h"
class Event
{
protected:
	bool isDone;
public:
	Event();
	~Event();
	bool IsDone() const { return isDone; }
	virtual bool Activate(Game* game) = 0;
};

