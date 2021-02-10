#include "stdafx.h"

#include "CLogger/include/Log.h"
#include "PlatformUtils.h"
#include "EClientRequestType.h"
#include "CServiceConnectionHandler.h"

CServiceConnectionHandler::CServiceConnectionHandler(CDataReceiver json_data) :
	m_json_data(json_data)
{
	InitPeerStream();
}

bool CServiceConnectionHandler::HandleEvent(const int socket_fd, EEventType type)
{
	bool result = true;
	switch (type) {
	case EEventType::REQUEST_DATA:
		result = HandleRequestEvent(socket_fd);
		break;
	case EEventType::CLOSE_EVENT:
		result = HandleResponseExitEvent(socket_fd);
		break;
	case EEventType::LOST_REQUEST:
		result = HandleWrongRequestEvent(socket_fd);
		break;
	}

	return result;
}

bool CServiceConnectionHandler::HandleRequestEvent(const int socket_fd)
{
	bool should_not_close_thread = false;
	std::string message;

	if (m_p_peer_stream->CanReceiveData(socket_fd) && 
		m_p_peer_stream->Receive(socket_fd, message))
	{
		if (IsEqualStrings(message, "ALL_DATA"))
		{
			CLOG_DEBUG_WITH_PARAMS("All data request from the socket ",
				socket_fd);
			 should_not_close_thread = HandleResponseEvent(socket_fd, 
				 EClientRequestType::ALL_DATA);
		}
		else if (IsEqualStrings(message, "DISK_DATA"))
		{
			CLOG_DEBUG_WITH_PARAMS("Disks data request from the socket ",
				socket_fd);
			should_not_close_thread = HandleResponseEvent(socket_fd, 
				EClientRequestType::DISKS_DATA);
		}
		else if (IsEqualStrings(message, "PROCESS_DATA"))
		{
			CLOG_DEBUG_WITH_PARAMS("Processes data request from the socket ",
				socket_fd);
			should_not_close_thread = HandleResponseEvent(socket_fd, 
				EClientRequestType::PROCESSES_DATA);
		}
		else if (IsEqualStrings(message, "DATA RECEIVED"))
		{
			should_not_close_thread = true;
		}
		else if (IsEqualStrings(message, "Exit"))
		{
			CLOG_DEBUG("Exit request from the client, handling close event");
			should_not_close_thread = !HandleEvent(socket_fd, 
				EEventType::CLOSE_EVENT);
		}
		else
		{
			CLOG_ERROR_WITH_PARAMS("Part of the data is lost, we receive", message);
			should_not_close_thread = HandleEvent(socket_fd, 
				EEventType::LOST_REQUEST);
		}

		CLOG_DEBUG_WITH_PARAMS("Should not close thread equal", should_not_close_thread);
	}
	else if (m_p_peer_stream->IsErrorOccured(socket_fd))
	{
		CLOG_ERROR_WITH_PARAMS("Lost connection with the client", socket_fd);
		should_not_close_thread = false;
		CLOG_DEBUG_WITH_PARAMS("value can_continue = ", should_not_close_thread);
	}

	return should_not_close_thread;
}

bool CServiceConnectionHandler::HandleResponseEvent(const int socket_fd,
	EClientRequestType type)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	std::string message;
	switch (type)
	{
	case EClientRequestType::ALL_DATA:
		CLOG_TRACE("Send all info to the client");
		message = m_json_data.GetAllInfo();
		break;
	case EClientRequestType::PROCESSES_DATA:
		CLOG_TRACE("Send process info to the client");
		message = m_json_data.GetProcessesInfo();
		break;
	case EClientRequestType::DISKS_DATA:
		CLOG_TRACE("Send disk info to the client");
		message = m_json_data.GetDisksInfo();
		break;
	default:
		CLOG_TRACE_WITH_PARAMS("Wrong parameter EClientRequestType, ",
			" cannot send response to the client");
		return false;
	}
	result = m_p_peer_stream->Send(socket_fd, message);
	CLOG_TRACE_WITH_PARAMS("Send function returned result ", result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CServiceConnectionHandler::HandleResponseExitEvent(const int socket_fd)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	CLOG_TRACE_WITH_PARAMS("Send exit response to the socket ", socket_fd,
		" client can disconnect");
	result = m_p_peer_stream->Send(socket_fd, "Disconnect");
	CLOG_DEBUG_WITH_PARAMS("Send function returned result ", result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CServiceConnectionHandler::HandleWrongRequestEvent(const int socket_fd)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	result = m_p_peer_stream->Send(socket_fd, "Request lost");
	result = HandleRequestEvent(socket_fd);
	CLOG_DEBUG_END_FUNCTION();

	return result;
}

bool CServiceConnectionHandler::IsEqualStrings(const std::string first_str, const std::string second_str) const
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
