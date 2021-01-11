#include "stdafx.h"

CAcceptor::CAcceptor(const int port, const std::string& address,
	CInitiationDispatcher* dispatcher)
	: m_dispatcher(dispatcher), m_address(address), m_port(port)
{
	m_peer_acceptor = std::make_unique<CAcceptorSocket>(port, address);
	HandleEvent(m_peer_acceptor.get()->GetHandle(), EventType::ACCEPT_EVENT);
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

void CAcceptor::HandleEvent(const int socket, EventType type)
{
	if (type == EventType::ACCEPT_EVENT)
	{
		int client_socket = m_peer_acceptor.get()->AcceptIncommingCalls();
		CServiceHandler* handler = new CServiceConnectionHandler(m_port,
				m_address,
				m_dispatcher);
		m_dispatcher->RegisterHandler(handler, EventType::READ_EVENT);
	}
}
