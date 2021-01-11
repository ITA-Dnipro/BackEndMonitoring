#pragma once
#include "CEventHandler.h"
// It is an interface for the class CInitiationDispatcher
class IDispatcher
{
public:
	virtual void RegisterHandler(CEventHandler* handler, EventType type) = 0;
	virtual void RemoveHandler(CEventHandler* handler, EventType type) = 0;
	virtual void HandleEvents(timeval* timeout = NULL) = 0;
};