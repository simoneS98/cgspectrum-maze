#pragma once
class Event
{
private:
	bool isDone;
public:
	Event();
	~Event();
	bool IsDone() { return isDone; }
	virtual bool Activate() = 0;
};

