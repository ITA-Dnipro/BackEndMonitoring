#include "CInitiationDispatcher.h"

namespace Dispatcher
{
	CInitiationDispatcher* CInitiationDispatcher::m_instance = nullptr;

	CInitiationDispatcher::CInitiationDispatcher()
	{ }

	CInitiationDispatcher* CInitiationDispatcher::GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new CInitiationDispatcher();
		}
		return m_instance;
	}

	void CInitiationDispatcher::RegisterHandler(Handler* handler, 
		EventHandler::EventType type)
    {
        m_storage.AddHandler(type, handler);
    }

    void CInitiationDispatcher::RemoveHandler(Handler* handler, 
		EventHandler::EventType type)
    {
        m_storage.RemoveHandler(handler->GetHandle());
    }

    void CInitiationDispatcher::HandleEvents(timeval* timeout)
    {
		fd_set read_fds, write_fds, except_fds;
		FD_ZERO(&read_fds);
		FD_ZERO(&write_fds);
		FD_ZERO(&except_fds);
		m_storage.ConvertToFdSet(read_fds, write_fds, except_fds);
		int maxfd = m_storage.GetMaxFd();
		int nResult = select(maxfd, &read_fds, &write_fds, &except_fds, 
			timeout);
		if (nResult <= 0) 
		{ 
			//error 
		}
		for (auto it = m_storage.GetBegin(); it != m_storage.GetEnd(); ++it)
		{
			if (FD_ISSET(it->second->GetHandle(), &read_fds))
			{
				if (it->first == EventHandler::EventType::READ_EVENT)
				{
					std::cout << "read";
					it->second->HandleEvent(it->second->GetHandle(), 
						EventHandler::EventType::READ_EVENT);
				}
			}
			if (FD_ISSET(it->second->GetHandle(), &write_fds))
			{
				if (it->first == EventHandler::EventType::WRITE_EVENT)
				{
					std::cout << "write";
					it->second->HandleEvent(it->second->GetHandle(), 
						EventHandler::EventType::WRITE_EVENT);
				}
			}
			if (FD_ISSET(it->second->GetHandle(), &except_fds))
			{
				if (it->first == EventHandler::EventType::CLOSE_EVENT)
				{
					it->second->HandleEvent(it->second->GetHandle(), 
						EventHandler::EventType::CLOSE_EVENT);
				}
			}
		}
    }

}
