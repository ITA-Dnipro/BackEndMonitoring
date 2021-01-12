#include "stdafx.h"
#include "CAcceptor.h"

CAcceptor::CAcceptor(const int port, const std::string& address)
	: m_address(address), m_port(port)
{
	m_peer_acceptor = std::make_unique<CAcceptorSocket>(port, address);
	HandleEvent(m_peer_acceptor->GetHandle(), EventType::ACCEPT_EVENT);
}

int CAcceptor::GetConnectedHandle()
{
	return m_peer_acceptor->AcceptIncommingCalls();
}

int CAcceptor::GetHandle() const
{
	return m_peer_acceptor->GetHandle();
}

void CAcceptor::HandleEvent(const int socket, EventType type)
{
	//if (type == EventType::ACCEPT_EVENT)
	//{
	//	int client_socket = m_peer_acceptor->AcceptIncommingCalls();
	//	std::shared_ptr<CSocketWrapper> stream = 
	//		std::make_shared<CSocketWrapper>(client_socket);
	//	CServiceHandler* handler = new CServiceConnectionHandler(stream,
	//			m_dispatcher);
	//	m_dispatcher->RegisterHandler(handler, EventType::REQUEST_DATA);
	//}
}
