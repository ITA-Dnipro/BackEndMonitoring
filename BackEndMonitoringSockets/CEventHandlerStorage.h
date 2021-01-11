#pragma once
#include <map>
#include "CEventHandler.h"
#include <WinSock2.h>

using CEH = EventHandler::CEventHandler;
using EventHandler::EventType;
namespace Storage
{
	class CEventHandlerStorage
	{
	public:
		CEventHandlerStorage();
		~CEventHandlerStorage();
		CEH* GetHandler(EventType event_type);
		void AddHandler(EventType event_type, CEH* event_handler);
		void RemoveHandler(const int handle);
		void ConvertToFdSet(fd_set& read_fds, fd_set& write_fds, 
			fd_set& except_fds);
		int GetMaxFd() const;
		int GetSize() const;
		std::map<EventType, CEH*>::const_iterator GetBegin() const;
		std::map<EventType, CEH*>::const_iterator GetEnd() const;

	private:
		std::map<EventType, CEH*> m_handlers_map;

	};
}
