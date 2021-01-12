#include "stdafx.h"
#include "CServiceConnectionHandler.h"

CServiceConnectionHandler::CServiceConnectionHandler(int socket)
	: m_server_socket(socket)
{
	m_peer_stream = std::make_unique<CSocketWrapper>(socket);
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

int CServiceConnectionHandler::GetHandle() const
{
	return m_peer_stream->GetHandle();
}

void CServiceConnectionHandler::HandleRequestEvent(const int socket)
{
	std::cout << "Request from the client " << socket << ": " << std::endl;
	std::cout << m_peer_stream->Receive(socket);
	HandleResponseEvent(socket);
}

void CServiceConnectionHandler::HandleResponseEvent(const int socket)
{
	std::cout << "The respone has been sent" << std::endl;
	m_peer_stream->Send(socket, data.GetData());
}

