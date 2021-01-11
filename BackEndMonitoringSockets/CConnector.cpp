#include "CConnector.h"

namespace Connector
{
	CConnector::CConnector(const int port, const std::string& ip_address, CDispatcher* dispathcer)
		: m_dispatcher(dispathcer), m_port(port), m_ip_address(ip_address)
	{
		m_socket_connector = std::make_unique<SockConn>(port, ip_address);
	}

	void CConnector::Connect(CSH* handler)
	{
		ConnectServiceHandler(handler);
	}

	int CConnector::GetHandle() const
	{
		return m_socket_connector.get()->GetHandle();
	}

	bool CConnector::ConnectServiceHandler(CSH* handler)
	{
		std::cout << "connect";
		if (m_socket_connector.get()->Connect())
		{
			RegisterHandler(handler);
			return true;
		}
		return false;
	}

	bool CConnector::Complete(const int handle)
	{
		CSH* service_handler = nullptr;

		auto sock_iterator = m_connection_map.find(handle);
		if (sock_iterator == m_connection_map.end()) {
			return false;
		}
		ServiceHandler::CServiceHandler* new_handler = (*sock_iterator).second;
		m_dispatcher->RemoveHandler(new_handler, EventHandler::EventType::WRITE_EVENT);
		m_connection_map.erase(sock_iterator);

		return true;
	}

	void CConnector::RegisterHandler(CSH* handler)
	{
		m_dispatcher->RegisterHandler(this, EventHandler::EventType::WRITE_EVENT);
		m_connection_map[m_socket_connector.get()->GetHandle()] = handler;
	}

	void CConnector::HandleEvent(const int socket, EventHandler::EventType type)
	{
		if (type == EventHandler::EventType::WRITE_EVENT)
		{
			Complete(socket);
		}
	}
}
