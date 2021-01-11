#pragma once
#include "stdafx.h"

// Base class for all the handlers
class CServiceHandler : public CEventHandler
{
public:
	virtual void HandleEvent(int socket, EventType type) = 0;
	virtual int GetHandle() const = 0;
};