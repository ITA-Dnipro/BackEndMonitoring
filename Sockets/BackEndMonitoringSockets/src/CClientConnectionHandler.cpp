#include "stdafx.h"

#include "CClientConnectionHandler.h"
#include "CLogger/include/Log.h"

CClientConnectionHandler::CClientConnectionHandler()
	: m_can_make_request(true), m_current_request()
{
	m_p_client_stream = InitClientStream();
}

bool CClientConnectionHandler::HandleEvent(const int socket_fd, 
	EEventType type, std::string& message)
{
	m_current_request = type;
	bool result = true;
	switch (type) {
	case EEventType::REQUEST_ALL_DATA:
		result = HandleRequestEvent(socket_fd, EEventType::REQUEST_ALL_DATA);
		break;
	case EEventType::REQUEST_DISK_DATA:
		result = HandleRequestEvent(socket_fd, EEventType::REQUEST_DISK_DATA);
		break;
	case EEventType::REQUEST_PROCESS_DATA:
		result = HandleRequestEvent(socket_fd, EEventType::REQUEST_PROCESS_DATA);
		break;
	case EEventType::CLOSE_EVENT:
		result = !(HandleExitEvent(socket_fd)); // If we can exit result equal false
		break;
	default:
		result = false;
		break;
	}

	if (result)
	{
		CLOG_DEBUG_WITH_PARAMS("Result is true, start HandleResponseEvent, for the socket", socket_fd);
		result = HandleResponseEvent(socket_fd, message);
	}

	return result;
}

bool CClientConnectionHandler::HandleRequestEvent(const int socket_fd, 
	EEventType type)
{
	std::string request_str = ConvertRequestToString(type);
	CLOG_DEBUG_WITH_PARAMS("Convert event type to the string", request_str);
	if (SendRequestToServer(socket_fd, request_str))
	{
		m_can_make_request = false;
		return true;
	}
	return false;
}

bool CClientConnectionHandler::HandleResponseEvent(const int socket_fd, 
	std::string& message)
{
	bool result = m_p_client_stream->Receive(socket_fd, message);

	if (result)
	{
		// If we get the wrong request from the server
		if (message.size() == 0 || message == "-1")
		{
			CLOG_ERROR_WITH_PARAMS("Response from the server", message);
			return false;
		}
		else if (message == "Request lost") // If we lost request
		{
			CLOG_ERROR_WITH_PARAMS("Response from the server", message);
			result = HandleLostRequestEvent(socket_fd, message);
		}
	}

	if (result)
	{
		return HandleDataReceivedEvent(socket_fd);
	}
	return false;
}

bool CClientConnectionHandler::HandleExitEvent(const int socket_fd)
{
	std::string response;

	if (SendRequestToServer(socket_fd, "Exit"))
	{
		m_p_client_stream->Receive(socket_fd, response);

		if (response == "Disconnect" || response == "-1")
		{
			return true;
		}
	}

	return true;
}

bool CClientConnectionHandler::HandleDataReceivedEvent(const int socket_fd)
{
	m_can_make_request = true;
	CLOG_DEBUG("Handle data received event");
	return m_p_client_stream->Send(socket_fd, "DATA RECEIVED");
}

bool CClientConnectionHandler::HandleLostRequestEvent(const int socket_fd, 
	std::string& message)
{
	const int max_trials = 10;
	int count_trials = 0;
	std::string request_str = ConvertRequestToString(m_current_request);
	while (count_trials++ < max_trials)
	{
		m_can_make_request = true;
		if (SendRequestToServer(socket_fd, request_str)
			&& m_p_client_stream->Receive(socket_fd, message))
		{
			m_can_make_request = false;
			if (message != "Request lost")
			{
				return true;
			}
			HandleDataReceivedEvent(socket_fd);
		}
	}
	return false;
}

bool CClientConnectionHandler::SendRequestToServer(const int socket_fd, 
	const std::string& request_message) 
{
	return m_p_client_stream->Send(socket_fd, request_message);
}

std::string CClientConnectionHandler::ConvertRequestToString(EEventType type) const
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
		request_str = "ERROR";
	}
	return request_str;
}

std::unique_ptr<CSocketWrapper> CClientConnectionHandler::InitClientStream()
{
	return std::move(std::make_unique<CSocketWrapper>());
}
