#include "CClientConnectionHandler.h"

ClientConHandler::CClientConnectionHandler::CClientConnectionHandler(EventHandler::EventType type, const SocketWrapper::CSocketWrapper& stream, CDispatcher* dispatcher)
{
	dispatcher->RegisterHandler(this, type);
}

void ClientConHandler::CClientConnectionHandler::HandleEvent(const int socket, EventHandler::EventType type)
{
	std::cout << socket;
	std::cout << static_cast<int>(type);

	if (type == EventHandler::EventType::READ_EVENT)
	{
		std::cout << m_client_stream.Receive(socket);
	}
	else if (type == EventHandler::EventType::WRITE_EVENT)
	{

		m_client_stream.Send(socket, "CClientConnectionHandler");
	}
	else if (type == EventHandler::EventType::CLOSE_EVENT)
	{
		m_client_stream.~CSocketWrapper();
		delete this;
	}
}

int ClientConHandler::CClientConnectionHandler::GetHandle() const
{
	return m_client_stream.GetHandle();
}
