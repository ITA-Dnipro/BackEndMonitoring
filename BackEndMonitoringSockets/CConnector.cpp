#include "stdafx.h"

CConnector::CConnector(const int port, const std::string& ip_address,
	CInitiationDispatcher* dispathcer)
	: m_dispatcher(dispathcer), m_port(port), m_ip_address(ip_address)
{
	m_socket_connector = std::make_unique<CConnectorSocket>(port, ip_address);
}

void CConnector::Connect(CServiceHandler* handler)
{
	ConnectServiceHandler(handler);
}

int CConnector::GetHandle() const
{
	return m_socket_connector.get()->GetHandle();
}

bool CConnector::ConnectServiceHandler(CServiceHandler* handler)
{
	if (m_socket_connector.get()->Connect())
	{
		RegisterHandler(handler);
		return true;
	}
	return false;
}

bool CConnector::Complete(const int handle)
{
	CServiceHandler* service_handler = nullptr;

	auto sock_iterator = m_connection_map.find(handle);
	if (sock_iterator == m_connection_map.end()) {
		return false;
	}
	CServiceHandler* new_handler = (*sock_iterator).second;
	m_dispatcher->RemoveHandler(new_handler, EventType::WRITE_EVENT);
	m_connection_map.erase(sock_iterator);

	return true;
}

void CConnector::RegisterHandler(CServiceHandler* handler)
{
	m_dispatcher->RegisterHandler(this,
		EventType::WRITE_EVENT);
	m_connection_map[m_socket_connector.get()->GetHandle()] = handler;
}

void CConnector::HandleEvent(const int socket, EventType type)
{
	if (type == EventType::WRITE_EVENT)
	{
		Complete(socket);
	}
}
