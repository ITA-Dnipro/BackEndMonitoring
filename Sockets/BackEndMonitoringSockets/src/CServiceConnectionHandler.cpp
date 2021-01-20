#include "stdafx.h"
#include "CServiceConnectionHandler.h"

CServiceConnectionHandler::CServiceConnectionHandler()
{
	m_peer_stream = InitPeerStream();
}

void CServiceConnectionHandler::HandleEvent(const int socket, EventType type)
{

	if (type == EventType::REQUEST_DATA)
	{
		HandleRequestEvent(socket);
	}
	else if (type == EventType::RESPONSE_DATA)
	{
		HandleResponseEvent(socket);
	}
}

void CServiceConnectionHandler::HandleRequestEvent(const int socket)
{
	std::cout << m_peer_stream->Receive(socket);
	HandleResponseEvent(socket);
}

void CServiceConnectionHandler::HandleResponseEvent(const int socket)
{
	m_peer_stream->Send(socket, data.GetData());
}

std::unique_ptr<CSocketWrapper> CServiceConnectionHandler::InitPeerStream()
{
	return std::move(std::make_unique<CSocketWrapper>());
}

