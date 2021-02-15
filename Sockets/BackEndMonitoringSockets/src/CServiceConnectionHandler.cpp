#include "stdafx.h"

#include "CLogger/include/Log.h"
#include "EClientRequestType.h"
#include "CServiceConnectionHandler.h"
#include "CSocketWrapper.h"
#include "CSocket.h"

CServiceConnectionHandler::CServiceConnectionHandler(CDataReceiver json_data) :
	m_json_data(json_data)
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
	case EEventType::LOST_REQUEST:
		CLOG_DEBUG("We lost request, start function HandleWrongRequestEvent");
		result = HandleWrongRequestEvent(client);
		break;
	default:
		CLOG_DEBUG("Default case in HandleEvent, return false");
		return false;
	}

	return result;
}

bool CServiceConnectionHandler::HandleRequestEvent(const CSocket& client_socket)
{
	bool should_not_close_client = false;
	std::string message;

	if (m_p_peer_stream->CanReceiveData(client_socket) &&
		m_p_peer_stream->Receive(client_socket, message))
	{
		switch(ParseMessageType(message))
		{
		case EClientRequestType::ALL_DATA:
			CLOG_DEBUG_WITH_PARAMS("All data request from the socket ",
				client_socket.GetSocketFD());
			should_not_close_client = HandleResponseEvent(client_socket,
				EClientRequestType::ALL_DATA);
			break;
		case EClientRequestType::DISKS_DATA:
			CLOG_DEBUG_WITH_PARAMS("Disks data request from the socket ",
				client_socket.GetSocketFD());
			should_not_close_client = HandleResponseEvent(client_socket,
				EClientRequestType::DISKS_DATA);
			break;
		case EClientRequestType::PROCESSES_DATA:
			CLOG_DEBUG_WITH_PARAMS("Processes data request from the socket ",
				client_socket.GetSocketFD());
			should_not_close_client = HandleResponseEvent(client_socket,
				EClientRequestType::PROCESSES_DATA);
			break;
		case EClientRequestType::DATA_RECEIVED:
			CLOG_DEBUG("Client has received his data");
			should_not_close_client = true;
			break;
		case EClientRequestType::EXIT:
			CLOG_DEBUG("Exit request from the client");
			should_not_close_client = false;
			break;
		case EClientRequestType::LOST_DATA:
			CLOG_ERROR_WITH_PARAMS("Part of the data is lost, we receive", message);
			should_not_close_client = HandleEvent(client_socket,
				EEventType::LOST_REQUEST);
			break;
		default:
			should_not_close_client = false;
			break;
		}

		CLOG_DEBUG_WITH_PARAMS("Should not close client equal", should_not_close_client);
	}
	else if (m_p_peer_stream->IsErrorOccurred(client_socket))
	{
		CLOG_ERROR_WITH_PARAMS("Lost connection with the client", 
			client_socket.GetSocketFD());
		should_not_close_client = false;
	}

	return should_not_close_client;
}

bool CServiceConnectionHandler::HandleResponseEvent(const CSocket& client_socket,
	EClientRequestType type)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	std::string message;
	switch (type)
	{
	case EClientRequestType::ALL_DATA:
		CLOG_DEBUG("Send all info to the client");
		message = m_json_data.GetAllInfo();
		break;
	case EClientRequestType::PROCESSES_DATA:
		CLOG_DEBUG("Send process info to the client");
		message = m_json_data.GetProcessesInfo();
		break;
	case EClientRequestType::DISKS_DATA:
		CLOG_DEBUG("Send disk info to the client");
		message = m_json_data.GetDisksInfo();
		break;
	default:
		CLOG_ERROR_WITH_PARAMS("Wrong parameter EClientRequestType, ",
			" cannot send response to the client");
		return false;
	}
	result = m_p_peer_stream->Send(client_socket, message);
	CLOG_DEBUG_WITH_PARAMS("Send function returned result ", result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CServiceConnectionHandler::HandleWrongRequestEvent(const CSocket& client_socket)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	result = m_p_peer_stream->Send(client_socket, "Request lost");
	result = HandleRequestEvent(client_socket);
	CLOG_DEBUG_END_FUNCTION();

	return result;
}

bool CServiceConnectionHandler::IsEqualStrings(const std::string& first_str, 
	const std::string& second_str) const
{
	CLOG_DEBUG_START_FUNCTION();
	for (size_t i = 0; i < second_str.size(); i++)
	{
		if (first_str[i] != second_str[i])
		{
			CLOG_DEBUG_WITH_PARAMS("This strings aren't equal", first_str, second_str);
			return false;
		}
	}
	CLOG_DEBUG_END_FUNCTION();
	return true;
}

void CServiceConnectionHandler::InitPeerStream()
{
	CLOG_DEBUG_START_FUNCTION();
	m_p_peer_stream = std::make_unique<CSocketWrapper>();
	CLOG_TRACE_VAR_CREATION(m_p_peer_stream);
	CLOG_DEBUG_END_FUNCTION();
}

EClientRequestType CServiceConnectionHandler::ParseMessageType(const 
	std::string& message) const
{
	EClientRequestType request_type = EClientRequestType::LOST_DATA;
	CLOG_DEBUG_START_FUNCTION();

	CLOG_DEBUG_WITH_PARAMS("We received request", message);
	for(int i = 0; i < g_c_requests_num; i++)
	{
		if(IsEqualStrings(g_c_requests_types[i], message))
		{
			CLOG_DEBUG("Correct request was found");
			request_type = static_cast<EClientRequestType>(i);
		}
	}
	CLOG_DEBUG_END_FUNCTION();

	return request_type;
}