#include "stdafx.h"

#include "CLogger/include/Log.h"
#include "PlatformUtils.h"
#include "EClientRequestType.h"

#include "CServiceConnectionHandler.h"



CServiceConnectionHandler::CServiceConnectionHandler(CDataReceiver json_data) :
	m_json_data(json_data)
{
	m_peer_stream = InitPeerStream();
}

bool CServiceConnectionHandler::HandleEvent(const int socket_fd, EventType type)
{
	bool can_continue = true;
	switch (type) {
	case EventType::REQUEST_DATA:
		can_continue = HandleRequestEvent(socket_fd);
		break;
	case EventType::CLOSE_EVENT:
		can_continue = HandleResponseExitEvent(socket_fd);
		break;
	}
	return can_continue;

}

bool CServiceConnectionHandler::HandleRequestEvent(const int socket_fd)
{
	bool can_continue = true;
	if (m_peer_stream->CanReceiveData(socket_fd))
	{
		std::string message = m_peer_stream->Receive(socket_fd);
		if (message == "ALL_DATA")
		{
			CLOG_DEBUG_WITH_PARAMS("All data request from the socket ", socket_fd);
			HandleResponseEvent(socket_fd, EClientRequestType::ALL_DATA);
		}
		else if (message == "DISK_DATA")
		{
			CLOG_DEBUG_WITH_PARAMS("Disks data request from the socket ", socket_fd);
			HandleResponseEvent(socket_fd, EClientRequestType::DISKS_DATA);
		}
		else if (message == "PROCESS_DATA")
		{
			CLOG_DEBUG_WITH_PARAMS("Processes data request from the socket ", socket_fd);
			HandleResponseEvent(socket_fd, EClientRequestType::PROCESSES_DATA);
		}
		else if (message == "Exit")
		{
			HandleEvent(socket_fd, EventType::CLOSE_EVENT);
			can_continue = false;
		}
	}
	return can_continue;
}

bool CServiceConnectionHandler::HandleResponseEvent(const int socket_fd, 
	EClientRequestType type)
{
	switch (type)
	{
	case EClientRequestType::ALL_DATA:
		return m_peer_stream->Send(socket_fd, m_json_data.GetAllInfo());
	case EClientRequestType::PROCESSES_DATA:
		return m_peer_stream->Send(socket_fd, m_json_data.GetProcessesInfo());
	case EClientRequestType::DISKS_DATA:
		return m_peer_stream->Send(socket_fd, m_json_data.GetDisksInfo());
	default:
		return false;
	}
}

bool CServiceConnectionHandler::HandleResponseExitEvent(const int socket_fd)
{
	return m_peer_stream->Send(socket_fd, "Disconnect");
}

std::unique_ptr<CSocketWrapper> CServiceConnectionHandler::InitPeerStream()
{
	return std::move(std::make_unique<CSocketWrapper>());
}

