#include "stdafx.h"

#include "CClientConnectionHandler.h"
#include "CSocket.h"
#include "CLogger/include/Log.h"
#include "GlobalVariable.h"

CClientConnectionHandler::CClientConnectionHandler()
{
	m_p_client_stream = InitClientStream();
}

bool CClientConnectionHandler::HandleEvent(const CSocket& client_socket,
	std::string& message, ERequestType req_typ, 
	ERequestRangeSpecification spec_typ,
	const std::string& date_of_start, const std::string& date_of_end)
{
	m_request_formatter.TryFormateRequest(message, req_typ, spec_typ, 
		date_of_start, date_of_end);

	// TODO make response handler here
	bool result = true;
	CLOG_DEBUG_START_FUNCTION();
	m_current_request = message;
	result = HandleRequestEvent(client_socket, message);

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
		// TODO wrong response + error from the server
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
	
	if(m_current_request.compare(GlobalVariable::c_request_error) == 0)
	{
		CLOG_ERROR("We receive error from the server");
		return false;
	}
	while (count_trials++ < max_trials)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		CLOG_DEBUG_WITH_PARAMS("Request data again", client_socket.GetSocketFD(), 
			m_current_request);
		// TODO wrong response from the server
		if (SendRequestToServer(client_socket, m_current_request)
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

std::unique_ptr<CSocketWrapper> CClientConnectionHandler::InitClientStream()
{
	CLOG_TRACE_START_FUNCTION();
	CLOG_TRACE_END_FUNCTION();
	return std::move(std::make_unique<CSocketWrapper>());
}
