#include "stdafx.h"

#include "CLogger/include/Log.h"
#include "EClientRequestType.h"
#include "CServiceConnectionHandler.h"
#include "CSocketWrapper.h"
#include "CSocket.h"

CServiceConnectionHandler::CServiceConnectionHandler(CDataProvider json_data) :
	m_json_data(json_data)
{
	InitPeerStream();
}

bool CServiceConnectionHandler::HandleEvent(const CSocket& client_socket, EEventType type)
{
	bool result = false;
	switch (type) {
	case EEventType::REQUEST_DATA:
		result = HandleRequestEvent(client_socket);
		break;
	case EEventType::LOST_REQUEST:
		result = HandleWrongRequestEvent(client_socket);
		break;
	default:
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
		if (IsEqualStrings(message, "ALL_DATA"))
		{
			CLOG_DEBUG_WITH_PARAMS("All data request from the socket ",
				client_socket.GetSocketFD());
			 should_not_close_client = HandleResponseEvent(client_socket,
				 EClientRequestType::ALL_DATA);
		}
		else if (IsEqualStrings(message, "DISK_DATA"))
		{
			CLOG_DEBUG_WITH_PARAMS("Disks data request from the socket ",
				client_socket.GetSocketFD());
			should_not_close_client = HandleResponseEvent(client_socket,
				EClientRequestType::DISKS_DATA);
		}
		else if (IsEqualStrings(message, "PROCESS_DATA"))
		{
			CLOG_DEBUG_WITH_PARAMS("Processes data request from the socket ",
				client_socket.GetSocketFD());
			should_not_close_client = HandleResponseEvent(client_socket,
				EClientRequestType::PROCESSES_DATA);
		}
		else if (IsEqualStrings(message, "DATA RECEIVED"))
		{
			should_not_close_client = true;
		}
		else if (IsEqualStrings(message, "Exit"))
		{
			CLOG_DEBUG("Exit request from the client");
			should_not_close_client = false;
		}
		else
		{
			CLOG_ERROR_WITH_PARAMS("Part of the data is lost, we receive", message);
			should_not_close_client = HandleEvent(client_socket,
				EEventType::LOST_REQUEST);
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
		CLOG_TRACE("Send all info to the client");
		message = m_json_data.GetAllFullInfo();
		break;
	case EClientRequestType::PROCESSES_DATA:
		CLOG_TRACE("Send process info to the client");
		message = m_json_data.GetProcessesFullInfo();
		break;
	case EClientRequestType::DISKS_DATA:
		CLOG_TRACE("Send disk info to the client");
		message = m_json_data.GetDisksFullInfo();
		break;
	default:
		CLOG_TRACE_WITH_PARAMS("Wrong parameter EClientRequestType, ",
			" cannot send response to the client");
		return false;
	}
	result = m_p_peer_stream->Send(client_socket, message);
	CLOG_TRACE_WITH_PARAMS("Send function returned result ", result);
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

bool CServiceConnectionHandler::IsEqualStrings(const std::string& first_str, const std::string& second_str) const
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
