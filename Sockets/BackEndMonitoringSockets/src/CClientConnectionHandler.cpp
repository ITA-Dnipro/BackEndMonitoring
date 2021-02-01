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
	case EventType::REQUEST_ALL_DATA:
		return HandleRequestEvent(socket_fd, EventType::REQUEST_ALL_DATA);
	case EventType::REQUEST_DISK_DATA:
		return HandleRequestEvent(socket_fd, EventType::REQUEST_DISK_DATA);
	case EventType::REQUEST_PROCESS_DATA:
		return HandleRequestEvent(socket_fd, EventType::REQUEST_PROCESS_DATA);
	case EventType::CLOSE_EVENT:
		HandleExitEvent(socket_fd);
		return false;
	default:
		return false;
	}
	return true;
}

bool CClientConnectionHandler::HandleRequestEvent(const int socket_fd, 
												  EventType type)
{
	std::string request_str;
	switch (type) {
	case EventType::REQUEST_ALL_DATA:
		request_str = "ALL_DATA";
		break;
	case EventType::REQUEST_DISK_DATA:
		request_str = "DISK_DATA";
		break;
	case EventType::REQUEST_PROCESS_DATA:
		request_str = "PROCESS_DATA";
		break;
	default:
		return false;
	}
	m_client_stream->Send(socket_fd, request_str);
	return HandleResponseEvent(socket_fd);
}

bool CClientConnectionHandler::HandleResponseEvent(const int socket_fd)
{
	std::string message = m_client_stream->Receive(socket_fd);
	if (message == "-1")
	{
		std::cout << "Error connection to the server, exit" << '\n';
		return false;
	}
	std::cout << message << '\n';
	return true;
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
