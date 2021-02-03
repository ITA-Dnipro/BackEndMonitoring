#include "stdafx.h"

#include "CClientConnectionHandler.h"

CClientConnectionHandler::CClientConnectionHandler() 
	: m_can_make_request(true)
{
	m_p_client_stream = InitClientStream();
}

bool CClientConnectionHandler::HandleEvent(const int socket_fd, 
	EEventType type, std::string& message)
{
	bool result = true;
	switch (type) {
	case EEventType::REQUEST_ALL_DATA:
		result = HandleRequestEvent(socket_fd, EEventType::REQUEST_ALL_DATA, 
			message);
		break;
	case EEventType::REQUEST_DISK_DATA:
		result = HandleRequestEvent(socket_fd, EEventType::REQUEST_DISK_DATA, 
			message);
		break;
	case EEventType::REQUEST_PROCESS_DATA:
		result = HandleRequestEvent(socket_fd, EEventType::REQUEST_PROCESS_DATA, 
			message);
		break;
	case EEventType::CLOSE_EVENT:
		if (HandleExitEvent(socket_fd, message) == true)
		{
			result = false;
		}
		break;
	default:
		result = false;
		break;
	}

	return result;
}

bool CClientConnectionHandler::HandleRequestEvent(const int socket_fd, 
	EEventType type, std::string& message)
{
	std::string request_str;
	switch (type) {
	case EEventType::REQUEST_ALL_DATA:
		request_str = "ALL_DATA";
		break;
	case EEventType::REQUEST_DISK_DATA:
		request_str = "DISK_DATA";
		break;
	case EEventType::REQUEST_PROCESS_DATA:
		request_str = "PROCESS_DATA";
		break;
	default:
		return false;
	}
	if (m_p_client_stream->Send(socket_fd, request_str) == false)
	{
		return false;
	}
	m_can_make_request = false;
	return HandleResponseEvent(socket_fd, message);
}

bool CClientConnectionHandler::HandleResponseEvent(const int socket_fd, 
	std::string& message)
{

	message = m_p_client_stream->Receive(socket_fd);
	if (message == "-1")
	{
		return false;
	}

	return HandleDataReceivedEvent(socket_fd);
}

bool CClientConnectionHandler::HandleExitEvent(const int socket_fd, 
	std::string& message)
{
	m_p_client_stream->Send(socket_fd, "Exit");

	while (true)
	{
		if (m_p_client_stream->Receive(socket_fd) == "Disconnect")
		{
			return true;
		}
	}
	return false;
}

bool CClientConnectionHandler::HandleDataReceivedEvent(const int socket_fd)
{
	m_can_make_request = true;
	return m_p_client_stream->Send(socket_fd, "DATA RECEIVED");
}

std::unique_ptr<CSocketWrapper> CClientConnectionHandler::InitClientStream()
{
	return std::move(std::make_unique<CSocketWrapper>());
}
