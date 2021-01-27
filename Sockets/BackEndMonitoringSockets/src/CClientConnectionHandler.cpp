#include "stdafx.h"
#include "CClientConnectionHandler.h"

CClientConnectionHandler::CClientConnectionHandler() 
{
	m_client_stream = InitClientStream();
}

void CClientConnectionHandler::HandleEvent(const int socket_fd, 
	EventType type)
{

	if (type == EventType::REQUEST_DATA)
	{
		HandleReadEvent(socket_fd);
	}
	else if (type == EventType::RESPONSE_DATA)
	{
		HandleReadEvent(socket_fd);
	}
}

void CClientConnectionHandler::HandleReadEvent(const int socket_fd)
{
	m_client_stream->Send(socket_fd, "Request for data\n");
	HandleWriteEvent(socket_fd);
}

void CClientConnectionHandler::HandleWriteEvent(const int socket_fd)
{
	std::cout << m_client_stream->Receive(socket_fd) << std::endl;
}

std::unique_ptr<CSocketWrapper> CClientConnectionHandler::InitClientStream()
{
	return std::move(std::make_unique<CSocketWrapper>());
}
