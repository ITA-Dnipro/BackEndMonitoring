#include "CServiceConnectionHandler.h"

namespace ServiceConHandler
{
	CServiceConnectionHandler::CServiceConnectionHandler(const int port, 
		const std::string& ip_address, CDispatcher* dispatcher)
	{
		m_peer_stream = std::make_unique<CStream>();
		m_dispatcher = dispatcher;
		m_dispatcher->RegisterHandler(this, EventHandler::EventType::WRITE_EVENT);
	}

	void CServiceConnectionHandler::HandleEvent(const int socket, 
		EventHandler::EventType type)
	{

		if (type == EventHandler::EventType::READ_EVENT)
		{
			std::cout << m_peer_stream.get()->Receive(socket);
		}
		else if (type == EventHandler::EventType::WRITE_EVENT)
		{
			m_peer_stream.get()->Send(socket, "TEST TEXT");
		}
		else if (type == EventHandler::EventType::CLOSE_EVENT)
		{
			m_peer_stream.get()->~CSocketWrapper();
			delete this;
		}
	}

	int CServiceConnectionHandler::GetHandle() const
	{
		return m_peer_stream.get()->GetHandle();
	}
}

