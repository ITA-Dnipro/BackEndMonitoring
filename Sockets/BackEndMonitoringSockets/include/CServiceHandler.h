#pragma once

enum class EventType
{
	REQUEST_DATA = 1,
	ACCEPT_EVENT = 1,
	RESPONSE_DATA = 2,
	TIMEOUT_EVENT = 3,
	SIGNAL_EVENT = 4,
	CLOSE_EVENT = 5,
};

// Base class for all the handlers
class CServiceHandler
{
public:
	virtual void HandleEvent(int socket, EventType type) = 0;
	virtual int GetHandle() const = 0;
};