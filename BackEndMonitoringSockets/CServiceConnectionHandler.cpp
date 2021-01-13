#include "stdafx.h"
#include "CServiceConnectionHandler.h"

CServiceConnectionHandler::CServiceConnectionHandler(int socket,
	std::shared_ptr<CLogger> logger)
	: m_server_socket(socket), m_logger(logger)
{
	m_peer_stream = InitPeerStream(socket);
}

void CServiceConnectionHandler::HandleEvent(const int socket, EventType type)
{

	if (type == EventType::REQUEST_DATA)
	{
		HandleRequestEvent(socket);
	}
	else if (type == EventType::RESPONSE_DATA)
	{
		HandleResponseEvent(socket);
	}
}

int CServiceConnectionHandler::GetHandle() const
{
	return m_peer_stream->GetHandle();
}

void CServiceConnectionHandler::HandleRequestEvent(const int socket)
{
	std::cout << "Request from the client " << socket << ": " << std::endl;
	std::cout << m_peer_stream->Receive(socket);
	Sleep(10000);
	HandleResponseEvent(socket);
}

void CServiceConnectionHandler::HandleResponseEvent(const int socket)
{
	std::cout << "The respone has been sent" << std::endl;
	m_peer_stream->Send(socket, data.GetData());
}

std::unique_ptr<CSocketWrapper> CServiceConnectionHandler::InitPeerStream
	(int handle)
{
	return std::move(std::make_unique<CSocketWrapper>(handle, m_logger));
}

