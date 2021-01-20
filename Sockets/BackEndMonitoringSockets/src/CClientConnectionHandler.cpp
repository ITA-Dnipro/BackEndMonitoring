#include "stdafx.h"
#include "CClientConnectionHandler.h"

CClientConnectionHandler::CClientConnectionHandler() 
{
	m_client_stream = InitClientStream();
}

void CClientConnectionHandler::HandleEvent(const int server_socket, 
	EventType type)
{

	if (type == EventType::REQUEST_DATA)
	{
		HandleReadEvent(server_socket);
	}
	else if (type == EventType::RESPONSE_DATA)
	{
		HandleReadEvent(server_socket);
	}
}

void CClientConnectionHandler::HandleReadEvent(int socket)
{
	m_client_stream->Send(socket, "Request for data\n");
	HandleWriteEvent(socket);
}

void CClientConnectionHandler::HandleWriteEvent(int socket)
{
	std::cout << m_client_stream->Receive(socket) << std::endl;
}

std::unique_ptr<CSocketWrapper> CClientConnectionHandler::InitClientStream()
{
	return std::move(std::make_unique<CSocketWrapper>());
}
