#include "stdafx.h"
#include "CClientConnectionHandler.h"

CClientConnectionHandler::CClientConnectionHandler(
	EventType type, const CSocketWrapper& stream, 
	CInitiationDispatcher* dispatcher)
{
	dispatcher->RegisterHandler(this, type);
}

void CClientConnectionHandler::HandleEvent(const int socket, EventType type)
{
	std::cout << socket;
	std::cout << static_cast<int>(type);

	if (type == EventType::READ_EVENT)
	{
		std::cout << m_client_stream.Receive(socket);
	}
	else if (type == EventType::WRITE_EVENT)
	{

		m_client_stream.Send(socket, "CClientConnectionHandler");
	}
	else if (type == EventType::CLOSE_EVENT)
	{
		m_client_stream.~CSocketWrapper();
		delete this;
	}
}

int CClientConnectionHandler::GetHandle() const
{
	return m_client_stream.GetHandle();
}
