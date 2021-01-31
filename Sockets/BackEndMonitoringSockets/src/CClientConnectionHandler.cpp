#include "stdafx.h"
#include "CClientConnectionHandler.h"

CClientConnectionHandler::CClientConnectionHandler() 
{
	m_client_stream = InitClientStream();
}

bool CClientConnectionHandler::HandleEvent(const int socket_fd, 
	EventType type)
{

	switch (type) {
	case EventType::REQUEST_DATA:
		HandleRequestEvent(socket_fd);
		break;
	case EventType::RESPONSE_DATA:
		HandleRequestEvent(socket_fd);
		break;
	case EventType::CLOSE_EVENT:
		HandleExitEvent(socket_fd);
		return false;
	}
	return true;
}

bool CClientConnectionHandler::HandleRequestEvent(const int socket_fd)
{
	m_client_stream->Send(socket_fd, "Request for data\n");
	return HandleResponseEvent(socket_fd);
}

bool CClientConnectionHandler::HandleResponseEvent(const int socket_fd)
{
	std::cout << m_client_stream->Receive(socket_fd) << '\n';
	return true;
	//TODO send data to client
	//m_response_holder.SetResponse(m_client_stream->Receive(socket_fd));
}

bool CClientConnectionHandler::HandleExitEvent(const int socket_fd)
{
	m_client_stream->Send(socket_fd, "Exit");

	while (true)
	{
		if (m_client_stream->Receive(socket_fd) != "Disconnect")
		{
			return false;
		}
	}
	return true;
}

std::unique_ptr<CSocketWrapper> CClientConnectionHandler::InitClientStream()
{
	return std::move(std::make_unique<CSocketWrapper>());
}
