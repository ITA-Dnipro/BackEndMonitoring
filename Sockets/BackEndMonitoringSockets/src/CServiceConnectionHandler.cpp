#include "stdafx.h"

#include "Log.h"
#include "CServiceConnectionHandler.h"
#include "CSocketWrapper.h"
#include "CSocket.h"
#include "GlobalVariable.h"

CServiceConnectionHandler::CServiceConnectionHandler(
	CRequestHandler request_handler) : m_request_handler(request_handler)
{
	InitPeerStream();
}

bool CServiceConnectionHandler::HandleEvent(const CSocket& client, EEventType event_type)
{
	bool result = false;
	switch (event_type) {
	case EEventType::REQUEST_DATA:
		CLOG_DEBUG_WITH_PARAMS("Request data from the client", client.GetSocketFD());
		result = HandleRequestEvent(client);
		break;
	default:
		CLOG_DEBUG("Default case in HandleEvent, return false");
		return false;
	}
	CLOG_TRACE_WITH_PARAMS("We have result work with client", result, client.GetSocketFD());
	return result;
}

bool CServiceConnectionHandler::HandleRequestEvent(const CSocket& client_socket)
{
	bool should_not_close_client = false;
	CLOG_DEBUG_START_FUNCTION();
	std::string message;
	std::string response_message;
	if (m_p_peer_stream->CanReceiveData(client_socket) &&
		m_p_peer_stream->Receive(client_socket, message))
	{
		CLOG_DEBUG_WITH_PARAMS("We receive request", message.c_str(), message.size());
		m_request_handler.HandleRequest(message, response_message);
		
		should_not_close_client = HandleResponseEvent(client_socket,
				response_message);

		CLOG_DEBUG_WITH_PARAMS("After sending result of work with client",
			should_not_close_client);
	}
	else if (m_p_peer_stream->IsErrorOccurred(client_socket))
	{
		CLOG_ERROR_WITH_PARAMS("Lost connection with the client",
			client_socket.GetSocketFD());
		should_not_close_client = false;
	}
	CLOG_DEBUG_END_FUNCTION();
	return should_not_close_client;
}

bool CServiceConnectionHandler::HandleResponseEvent(const CSocket& client_socket,
	const std::string& response_message)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	result = m_p_peer_stream->Send(client_socket, response_message);
	CLOG_DEBUG_WITH_PARAMS("Send function returned result ", result,
		client_socket.GetSocketFD(), "We sent bytes", response_message.size());
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

void CServiceConnectionHandler::InitPeerStream()
{
	CLOG_DEBUG_START_FUNCTION();
	m_p_peer_stream = std::make_unique<CSocketWrapper>();
	CLOG_TRACE_VAR_CREATION(m_p_peer_stream);
	CLOG_DEBUG_END_FUNCTION();
}
