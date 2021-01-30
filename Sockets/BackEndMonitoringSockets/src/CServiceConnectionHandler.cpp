#include "stdafx.h"

#include "CLogger/include/Log.h"
#include "PlatformUtils.h"

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
		if (message == "Request for data\n")
		{
			CLOG_DEBUG_WITH_PARAMS("Data request from the socket ", socket_fd);
			HandleResponseEvent(socket_fd);
		}
		else if (message == "Exit")
		{
			HandleEvent(socket_fd, EventType::CLOSE_EVENT);
			can_continue = false;
		}
	}
	return can_continue;
}

bool CServiceConnectionHandler::HandleResponseEvent(const int socket_fd)
{
	return m_peer_stream->Send(socket_fd, m_json_data.GetAllInfo());
}

bool CServiceConnectionHandler::HandleResponseExitEvent(const int socket_fd)
{
	return m_peer_stream->Send(socket_fd, "Disconnect");
}

std::unique_ptr<CSocketWrapper> CServiceConnectionHandler::InitPeerStream()
{
	return std::move(std::make_unique<CSocketWrapper>());
}

