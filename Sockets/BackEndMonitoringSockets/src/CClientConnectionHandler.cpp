#include "stdafx.h"

#include "CClientConnectionHandler.h"
#include "CSocket.h"
#include "CLogger/include/Log.h"
#include "GlobalVariable.h"

CClientConnectionHandler::CClientConnectionHandler()
	: m_current_request(EEventType::REQUEST_ALL_DATA)
{
	m_p_client_stream = InitClientStream();
}

bool CClientConnectionHandler::HandleEvent(const CSocket& client_socket,
	EEventType type, std::string& message)
{
	bool result = true;
	CLOG_DEBUG_START_FUNCTION();
	m_current_request = type;
	switch (type) {
	case EEventType::REQUEST_ALL_DATA:
		CLOG_DEBUG("Request all data");
		result = HandleRequestEvent(client_socket, EEventType::REQUEST_ALL_DATA);
		break;
	case EEventType::REQUEST_DISK_DATA:
		CLOG_DEBUG("Request disk data");
		result = HandleRequestEvent(client_socket, EEventType::REQUEST_DISK_DATA);
		break;
	case EEventType::REQUEST_PROCESS_DATA:
		CLOG_DEBUG("Request process data");
		result = HandleRequestEvent(client_socket, EEventType::REQUEST_PROCESS_DATA);
		break;
	case EEventType::CLOSE_EVENT:
		CLOG_DEBUG("Request exit");
		HandleExitEvent(client_socket); // If we can exit result equal false
		return false;
	default:
		result = false;
		break;
	}
	CLOG_DEBUG_WITH_PARAMS("Result after HandleRequestEvent is equal", result);
	if (result)
	{
		CLOG_DEBUG_WITH_PARAMS("Start HandleResponseEvent, for the socket", 
			client_socket.GetSocketFD());
		result = HandleResponseEvent(client_socket, message);
	}
	CLOG_DEBUG_END_FUNCTION();

	return result;
}

bool CClientConnectionHandler::HandleRequestEvent(const CSocket& client_socket,
	EEventType type) const
{
	CLOG_DEBUG_START_FUNCTION();

	std::string request_str = ConvertRequestToString(type);
	CLOG_DEBUG_WITH_PARAMS("Convert event type to the string", request_str);
	if (SendRequestToServer(client_socket, request_str))
	{
		return true;
	}
	CLOG_DEBUG_END_FUNCTION();

	return false;
}

bool CClientConnectionHandler::HandleResponseEvent(const CSocket& client_socket,
	std::string& message)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();

	result = m_p_client_stream->Receive(client_socket, message);
	CLOG_DEBUG_WITH_PARAMS("We send request to the server, result", result);
	if (result)
	{
		if (message.compare(GlobalVariable::c_connection_problem) == 0)
		{
			CLOG_ERROR_WITH_PARAMS("Response from the server", message);
			return false;
		}
		else if (message.compare(GlobalVariable::c_lost_request) == 0)
		{
			CLOG_ERROR_WITH_PARAMS("Response from the server", message);
			result = HandleLostRequestEvent(client_socket, message);
		}
	}

	if(!result)
	{
		CLOG_DEBUG("Start HandleLostRequestEvent");
		result = HandleLostRequestEvent(client_socket, message);
	}
	CLOG_DEBUG_END_FUNCTION();

	return result;
}

bool CClientConnectionHandler::HandleExitEvent(const CSocket& client_socket)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	result = SendRequestToServer(client_socket, GlobalVariable::c_exit_message);
	CLOG_DEBUG_WITH_PARAMS("HandleExitEvent send exit message", result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CClientConnectionHandler::HandleLostRequestEvent(const CSocket& client_socket,
	std::string& message)
{
	CLOG_DEBUG_START_FUNCTION();

	const int max_trials = 5;
	int count_trials = 0;
	std::string request_str = ConvertRequestToString(m_current_request);

	if(request_str.compare(GlobalVariable::c_request_error) == 0)
	{
		CLOG_ERROR("We receive error from the server");
		return false;
	}
	while (count_trials++ < max_trials)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		CLOG_DEBUG_WITH_PARAMS("Request data again", client_socket.GetSocketFD(), 
			request_str);
		if (SendRequestToServer(client_socket, request_str)
			&& m_p_client_stream->Receive(client_socket, message))
		{
			CLOG_DEBUG_WITH_PARAMS("We receive response", message.size());
			if (!message.empty() 
				&& message.compare(GlobalVariable::c_lost_request) != 0 
				&& message.compare(GlobalVariable::c_connection_problem) != 0)
			{
				CLOG_DEBUG("We receive correct response");
				return true;
			}
		}
	}
	CLOG_DEBUG_END_FUNCTION();
	return false;
}

bool CClientConnectionHandler::SendRequestToServer(const CSocket& client_socket,
	const std::string& request_message) const
{
	bool result = false;
	CLOG_TRACE_START_FUNCTION();
	result = m_p_client_stream->Send(client_socket, request_message);
	CLOG_DEBUG_WITH_PARAMS("Result of sending request to the server", result);
	CLOG_TRACE_END_FUNCTION();
	return result;
}

std::string CClientConnectionHandler::ConvertRequestToString(EEventType type) const
{
	std::string request_str;
	CLOG_TRACE_START_FUNCTION();

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
		request_str = GlobalVariable::c_request_error;
	}
	CLOG_DEBUG_WITH_PARAMS("We have request", request_str);
	CLOG_TRACE_END_FUNCTION();
	return request_str;
}

std::unique_ptr<CSocketWrapper> CClientConnectionHandler::InitClientStream()
{
	CLOG_TRACE_START_FUNCTION();
	CLOG_TRACE_END_FUNCTION();
	return std::move(std::make_unique<CSocketWrapper>());
}
