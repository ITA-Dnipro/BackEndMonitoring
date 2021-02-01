#pragma once

enum class EventType
{
	REQUEST_DATA = 1,
	REQUEST_ALL_DATA = 2,
	REQUEST_PROCESS_DATA = 3,
	REQUEST_DISK_DATA = 4,
	ACCEPT_EVENT = 5,
	RESPONSE_DATA = 6,
	TIMEOUT_EVENT = 7,
	SIGNAL_EVENT = 8,
	CLOSE_EVENT = 9,
};

// Base class for all the handlers
class CServiceHandler
{
public:
	virtual bool HandleEvent(const int socket_fd, EventType type) = 0;
};