#include "stdafx.h"

#include "CLogger/include/Log.h"
#include "PlatformUtils.h"
#include "EClientRequestType.h"
#include "CServiceConnectionHandler.h"

CServiceConnectionHandler::CServiceConnectionHandler(CDataReceiver json_data) :
	m_json_data(json_data), m_can_receive_data(true)
{
	InitPeerStream();
}

bool CServiceConnectionHandler::HandleEvent(const int socket_fd, EEventType type)
{
	bool can_continue = true;
	switch (type) {
	case EEventType::REQUEST_DATA:
		can_continue = HandleRequestEvent(socket_fd);
		break;
	case EEventType::CLOSE_EVENT:
		can_continue = HandleResponseExitEvent(socket_fd);
		break;
	}
	return can_continue;
}

bool CServiceConnectionHandler::HandleRequestEvent(const int socket_fd)
{
	bool can_continue = true;
	if (m_p_peer_stream->CanReceiveData(socket_fd))
	{
		std::string message = m_p_peer_stream->Receive(socket_fd);
		if (m_can_receive_data && message == "ALL_DATA")
		{
			CLOG_TRACE_WITH_PARAMS("All data request from the socket ", 
				socket_fd);
			m_can_receive_data = false;
			HandleResponseEvent(socket_fd, EClientRequestType::ALL_DATA);
		}
		else if (m_can_receive_data && message == "DISK_DATA")
		{
			CLOG_TRACE_WITH_PARAMS("Disks data request from the socket ",
				socket_fd);
			m_can_receive_data = false;
			HandleResponseEvent(socket_fd, EClientRequestType::DISKS_DATA);
		}
		else if (m_can_receive_data && message == "PROCESS_DATA")
		{
			CLOG_TRACE_WITH_PARAMS("Processes data request from the socket ",
				socket_fd);
			m_can_receive_data = false;
			HandleResponseEvent(socket_fd, EClientRequestType::PROCESSES_DATA);
		}
		else if (!m_can_receive_data && message == "DATA RECEIVED")
		{
			m_can_receive_data = true;
		}
		else if (message == "Exit")
		{
			CLOG_TRACE("Exit request from the client, handling close event");
			HandleEvent(socket_fd, EEventType::CLOSE_EVENT);
			can_continue = false;
		}
		
		CLOG_TRACE_WITH_PARAMS("value can_continue = ", can_continue);
	}

	int error = 0;
	if ((error = PlatformUtils::GetConnectionError(socket_fd)) == 10054)
	{
		CLOG_TRACE_WITH_PARAMS("ERROR!!! On the socket ", socket_fd,
			" has occured error ", error);
		can_continue = false;
		CLOG_DEBUG_WITH_PARAMS("value can_continue = ", can_continue);
	}
	return can_continue;
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
		CLOG_TRACE("Send dick info to the client");
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

void CServiceConnectionHandler::InitPeerStream()
{
	CLOG_DEBUG_START_FUNCTION();
	m_p_peer_stream = std::make_unique<CSocketWrapper>();
	CLOG_TRACE_VAR_CREATION(m_p_peer_stream);
	CLOG_DEBUG_END_FUNCTION();
}

