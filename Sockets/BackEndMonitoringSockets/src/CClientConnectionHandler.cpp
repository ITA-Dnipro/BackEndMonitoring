#include "stdafx.h"

#include "CClientConnectionHandler.h"
#include "CSocket.h"
#include "CLogger/include/Log.h"

CClientConnectionHandler::CClientConnectionHandler()
	: m_current_request(EEventType::REQUEST_ALL_DATA)
{
	m_p_client_stream = InitClientStream();
}

bool CClientConnectionHandler::HandleEvent(const CSocket& client_socket,
	EEventType type, std::string& message)
{
	m_current_request = type;
	bool result = true;
	switch (type) {
	case EEventType::REQUEST_ALL_DATA:
		result = HandleRequestEvent(client_socket, EEventType::REQUEST_ALL_DATA);
		break;
	case EEventType::REQUEST_DISK_DATA:
		result = HandleRequestEvent(client_socket, EEventType::REQUEST_DISK_DATA);
		break;
	case EEventType::REQUEST_PROCESS_DATA:
		result = HandleRequestEvent(client_socket, EEventType::REQUEST_PROCESS_DATA);
		break;
	case EEventType::CLOSE_EVENT:
		HandleExitEvent(client_socket); // If we can exit result equal false
		return false;
	default:
		result = false;
		break;
	}

	if (result)
	{
		CLOG_DEBUG_WITH_PARAMS("Start HandleResponseEvent, for the socket", 
			client_socket.GetSocketFD());
		result = HandleResponseEvent(client_socket, message);
	}

	return result;
}

bool CClientConnectionHandler::HandleRequestEvent(const CSocket& client_socket,
	EEventType type) const
{
	std::string request_str = ConvertRequestToString(type);
	CLOG_DEBUG_WITH_PARAMS("Convert event type to the string", request_str);
	if (SendRequestToServer(client_socket, request_str))
	{
		return true;
	}
	return false;
}

bool CClientConnectionHandler::HandleResponseEvent(const CSocket& client_socket,
	std::string& message)
{
	bool result = m_p_client_stream->Receive(client_socket, message);
	CLOG_DEBUG_WITH_PARAMS("We send request to the server, result", result);
	if (result)
	{
		// If we get the wrong request from the server
		if (message.compare("-1") == c_equal)
		{
			CLOG_ERROR_WITH_PARAMS("Response from the server", message);
			return false;
		}
		else if (message.compare("Request lost") == c_equal) // If we lost request
		{
			CLOG_ERROR_WITH_PARAMS("Response from the server", message);
			result = HandleLostRequestEvent(client_socket, message);
		}
	}

	if(result)
	{
		return HandleDataReceivedEvent(client_socket);
	}

	return false;
}

bool CClientConnectionHandler::HandleExitEvent(const CSocket& client_socket)
{
	return SendRequestToServer(client_socket, "Exit");
}

bool CClientConnectionHandler::HandleDataReceivedEvent(const CSocket& 
	client_socket) const
{
	CLOG_DEBUG("Handle data received event");
	return m_p_client_stream->Send(client_socket, "DATA RECEIVED");
}

bool CClientConnectionHandler::HandleLostRequestEvent(const CSocket& client_socket,
	std::string& message)
{
	const int max_trials = 5;
	int count_trials = 0;
	std::string request_str = ConvertRequestToString(m_current_request);

	if(request_str.compare("ERROR") == c_equal)
	{
		return false;
	}
	while (count_trials++ < max_trials)
	{
		if (SendRequestToServer(client_socket, request_str)
			&& m_p_client_stream->Receive(client_socket, message))
		{
			if (!message.empty() && message.compare("Request lost") != c_equal 
				&& message.compare("-1") != c_equal)
			{
				return HandleDataReceivedEvent(client_socket);
			}
		}
	}
	return false;
}

bool CClientConnectionHandler::SendRequestToServer(const CSocket& client_socket,
	const std::string& request_message) const
{
	return m_p_client_stream->Send(client_socket, request_message);
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
