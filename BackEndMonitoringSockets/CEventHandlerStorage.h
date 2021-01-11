#pragma once
#include "stdafx.h"

// This class is a storage for all types of events
class CEventHandlerStorage
{
public:
	CEventHandlerStorage();
	~CEventHandlerStorage();
	CEventHandler* GetHandler(EventType event_type);
	void AddHandler(EventType event_type, CEventHandler* event_handler);
	void RemoveHandler(const int handle);
	void ConvertToFdSet(fd_set& read_fds, fd_set& write_fds,
		fd_set& except_fds);
	int GetMaxFd() const;
	int GetSize() const;
	std::map<EventType, CEventHandler*>::const_iterator GetBegin() const;
	std::map<EventType, CEventHandler*>::const_iterator GetEnd() const;

private:
	std::map<EventType, CEventHandler*> m_handlers_map;

};