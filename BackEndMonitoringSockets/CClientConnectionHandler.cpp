#include "stdafx.h"
#include "CClientConnectionHandler.h"

CClientConnectionHandler::CClientConnectionHandler(int client_socket)
	: m_socket(client_socket)
{
	m_client_stream = std::make_unique<CSocketWrapper>(client_socket);
}

void CClientConnectionHandler::HandleEvent(const int server_socket, EventType type)
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

int CClientConnectionHandler::GetHandle() const
{
	return m_client_stream->GetHandle();
}

void CClientConnectionHandler::HandleReadEvent(int socket)
{
	m_client_stream->Send(socket, "Request for data\n");
	Sleep(10000);
	HandleWriteEvent(socket);
}

void CClientConnectionHandler::HandleWriteEvent(int socket)
{
	std::cout << "the response from the server" << std::endl;
	std::cout << m_client_stream->Receive(socket) << std::endl;
}
