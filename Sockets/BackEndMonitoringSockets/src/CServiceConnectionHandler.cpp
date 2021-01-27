#include "stdafx.h"
#include "CServiceConnectionHandler.h"

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
	static int count = 0;
	std::string message = m_peer_stream->Receive(socket_fd);
	if (message == "Request for data\n")
	{
		std::cout << message << " " << std::to_string(++count) << std::endl;
		HandleResponseEvent(socket_fd);
	}
	else
	{
		HandleResponseEvent(socket_fd);
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

