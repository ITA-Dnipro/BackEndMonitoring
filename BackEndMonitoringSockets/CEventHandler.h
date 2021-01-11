#pragma once

// Types of events
enum class EventType
{
	READ_EVENT = 1,
	ACCEPT_EVENT = 1,
	WRITE_EVENT = 2,
	TIMEOUT_EVENT = 3,
	SIGNAL_EVENT = 4,
	CLOSE_EVENT = 5,
};

// Base class for Accepotor, Connector and all handlers
class CEventHandler
{
public:
	virtual ~CEventHandler();

	virtual void HandleEvent(const int socket, EventType type) = 0;
	virtual int GetHandle() const = 0;
};
