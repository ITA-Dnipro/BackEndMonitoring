#include "stdafx.h"

#include "CSocket.h"
#include "CLogger/include/Log.h"
#include "GlobalVariable.h"

#include "CClientConnectionHandler.h"

CClientConnectionHandler::CClientConnectionHandler()
{
	m_p_client_stream = InitClientStream();
}

bool CClientConnectionHandler::HandleEvent(const CSocket& client_socket,
	std::string& message, ERequestType req_typ, EFrameError error,
	ERequestRangeSpecification spec_typ,
	const std::string& date_of_start, const std::string& date_of_end)
{
	bool result = m_request_formatter.TryFormateRequest(message, req_typ, error, spec_typ,
		date_of_start, date_of_end);

	CLOG_DEBUG_START_FUNCTION();
	m_current_request = message;
	result = HandleRequestEvent(client_socket, message);
	message.clear();
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
	const std::string& request) const
{
	CLOG_DEBUG_START_FUNCTION();

	if (SendRequestToServer(client_socket, request))
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
		
		if (m_response_handler.GetErrorCodeFromFrame(message) == EFrameError::CONNECTION_PROBLEM)
		{
			CLOG_ERROR_WITH_PARAMS("Response from the server", message);
			return false;
		}
		else if (m_response_handler.GetErrorCodeFromFrame(message) == EFrameError::LOST_REQUEST)
		{
			CLOG_ERROR_WITH_PARAMS("Response from the server", message);
			result = HandleLostRequestEvent(client_socket, message);
		}

		json_format = nlohmann::json::parse(message);
		std::string guid = 
			json_format[GlobalVariable::c_request_key_id].get<std::string>();
		result = m_response_handler.HandleResponse(guid, message, message);
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
	std::string exit_message;
	result = m_request_formatter.TryFormateRequest(exit_message, 
		ERequestType::EXIT, EFrameError::EXIT_MESSAGE);

	if(result)
	{
		result = SendRequestToServer(client_socket, exit_message);
	}
	
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

	if(m_response_handler.GetErrorCodeFromFrame(message) == EFrameError::INCORRECT_REQUEST)
	{
		CLOG_ERROR("We receive error from the server");
		return false;
	}
	while (count_trials++ < max_trials)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		CLOG_DEBUG_WITH_PARAMS("Request data again", client_socket.GetSocketFD(), 
			m_current_request);

		if (SendRequestToServer(client_socket, m_current_request)
			&& m_p_client_stream->Receive(client_socket, message))
		{
			CLOG_DEBUG_WITH_PARAMS("We receive response", message.size());
			if (!message.empty() 
				&& m_response_handler.GetErrorCodeFromFrame(message) != EFrameError::LOST_REQUEST
				&& m_response_handler.GetErrorCodeFromFrame(message) != EFrameError::CONNECTION_PROBLEM)
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

std::unique_ptr<CSocketWrapper> CClientConnectionHandler::InitClientStream()
{
	CLOG_TRACE_START_FUNCTION();
	CLOG_TRACE_END_FUNCTION();
	return std::move(std::make_unique<CSocketWrapper>());
}
