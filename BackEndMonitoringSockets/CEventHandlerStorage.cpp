#include "CEventHandlerStorage.h"

namespace Storage
{

	CEventHandlerStorage::CEventHandlerStorage()
	{
	}

	CEventHandlerStorage::~CEventHandlerStorage()
	{
		for (auto it = m_handlers_map.begin(); it != m_handlers_map.end(); it++)
		{
			delete it->second;
		}
		m_handlers_map.clear();
	}

	CEH* CEventHandlerStorage::GetHandler(EventHandler::EventType event_type)
	{
		CEH* event_handler = m_handlers_map[event_type];

		if (event_handler != nullptr) {
			return event_handler;
		}

		return nullptr;
	}

	void CEventHandlerStorage::AddHandler(EventHandler::EventType event_type, CEH* event_handler)
	{
		if (m_handlers_map.count(event_type))
		{
			m_handlers_map[event_type] = event_handler;
		}
		else
		{
			m_handlers_map.insert(std::make_pair(event_type, event_handler));
		}
	}

	void CEventHandlerStorage::RemoveHandler(const int handle)
	{
		for (auto it = m_handlers_map.begin(); it != m_handlers_map.end(); ++it)
		{
			if(it->second->GetHandle() == handle)
			{
				delete it->second;
				m_handlers_map.erase(it);
			}
		}
	}

	void CEventHandlerStorage::ConvertToFdSet(fd_set& read_fds, fd_set& write_fds, fd_set& except_fds)
	{
		for (auto it = m_handlers_map.begin(); it != m_handlers_map.end(); ++it)
		{
			if (it->first == EventHandler::EventType::READ_EVENT) {
				FD_SET(it->second->GetHandle(), &read_fds);
			}
			else if (it->first == EventHandler::EventType::WRITE_EVENT)
			{
				FD_SET(it->second->GetHandle(), &write_fds);
			}
			else if (it->first == EventHandler::EventType::TIMEOUT_EVENT)
			{
				FD_SET(it->second->GetHandle(), &except_fds);
			}
		}
	}

	int CEventHandlerStorage::GetMaxFd() const
	{
		int max_fd = 0;
		for(auto it = m_handlers_map.begin(); it != m_handlers_map.end(); ++it)
		{
			if (max_fd < it->second->GetHandle())
			{
				max_fd = it->second->GetHandle();
			}
		}
		return max_fd;
	}

	int CEventHandlerStorage::GetSize() const
	{
		return m_handlers_map.size();
	}

	std::map<EventHandler::EventType, CEH*>::const_iterator CEventHandlerStorage::GetBegin() const
	{
		return m_handlers_map.begin();
	}

	std::map<EventHandler::EventType, CEH*>::const_iterator CEventHandlerStorage::GetEnd() const
	{
		return m_handlers_map.end();
	}

}