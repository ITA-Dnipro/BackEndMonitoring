#include "CAcceptor.h"

namespace Acceptor
{
	CAcceptor::CAcceptor(const int port, const std::string& address, CDispatcher* dispatcher)
		:  m_dispatcher(dispatcher), m_address(address), m_port(port)
	{
		dispatcher->RegisterHandler(this, EventHandler::EventType::ACCEPT_EVENT);
		m_peer_acceptor = std::make_unique<AcceptorSocket::CAcceptorSocket>(port, address);
	}

	bool CAcceptor::Listening()
	{
		int socket = m_peer_acceptor.get()->AcceptIncommingCalls();
		if (socket != -1)
		{
			std::cout << socket << std::endl;
			return true;
		}
		return false;
	}

	int CAcceptor::GetHandle() const
	{
		return m_peer_acceptor.get()->GetHandle();
	}

	void CAcceptor::HandleEvent(const int socket, EventHandler::EventType type)
	{
		if (type == EventHandler::EventType::ACCEPT_EVENT) 
		{
			int client_socket = m_peer_acceptor.get()->AcceptIncommingCalls();
			ServiceHandler::CServiceHandler* handler = new ServiceConHandler::CServiceConnectionHandler(m_port, m_address, m_dispatcher);
			m_dispatcher->RegisterHandler(handler, EventHandler::EventType::READ_EVENT);
		}
	}


}
