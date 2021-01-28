#include "stdafx.h"
#include "CServiceConnectionHandler.h"
#include "CLogger/include/Log.h"

CServiceConnectionHandler::CServiceConnectionHandler()
{
	m_peer_stream = InitPeerStream();
}

void CServiceConnectionHandler::HandleEvent(const int socket_fd, EventType type)
{

	if (type == EventType::REQUEST_DATA)
	{
		HandleRequestEvent(socket_fd);
	}
	else if (type == EventType::RESPONSE_DATA)
	{
		HandleResponseEvent(socket_fd);
	}
}

void CServiceConnectionHandler::HandleRequestEvent(const int socket_fd)
{
	static std::atomic<int> count{0};

	if (m_peer_stream->CanReceiveData(socket_fd))
	{
		std::string message = m_peer_stream->Receive(socket_fd);
		if (message == "Request for data\n")
		{
			CLOG_DEBUG_WITH_PARAMS("Data request from the socket ", socket_fd, 
				" number of the request ", count.load());
			HandleResponseEvent(socket_fd);
		}
	}
}

void CServiceConnectionHandler::HandleResponseEvent(const int socket_fd)
{
	m_peer_stream->Send(socket_fd, data.GetData());
}

std::unique_ptr<CSocketWrapper> CServiceConnectionHandler::InitPeerStream()
{
	return std::move(std::make_unique<CSocketWrapper>());
}

