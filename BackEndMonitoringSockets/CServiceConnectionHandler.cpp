#include "stdafx.h"
#include "CServiceConnectionHandler.h"

CServiceConnectionHandler::CServiceConnectionHandler(const int port,
	const std::string& ip_address, CInitiationDispatcher* dispatcher)
{
	m_peer_stream = std::make_unique<CSocketWrapper>();
	m_dispatcher = dispatcher;
	m_dispatcher->RegisterHandler(this, EventType::WRITE_EVENT);
}

void CServiceConnectionHandler::HandleEvent(const int socket, EventType type)
{

	if (type == EventType::READ_EVENT)
	{
		std::cout << m_peer_stream->Receive(socket);
	}
	else if (type == EventType::WRITE_EVENT)
	{
		m_peer_stream->Send(socket, "TEST TEXT");
	}
	else if (type == EventType::CLOSE_EVENT)
	{
		m_peer_stream->~CSocketWrapper();
		delete this;
	}
}

int CServiceConnectionHandler::GetHandle() const
{
	return m_peer_stream->GetHandle();
}
