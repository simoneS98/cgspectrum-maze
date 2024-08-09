#include "Event.h"
Event::Event()
	: isDone(false)
	, m_pCallback(nullptr)
{
}
/*
Event::Event(void(*callback)(void))
	: isDone(false)
	, m_pCallback(callback)
{
}
*/
Event::~Event()
{
}
