#include "stdafx.h"
#include "CConnector.h"

CConnector::CConnector(const int port, const std::string& ip_address)
	: m_port(port), m_ip_address(ip_address)
{
	m_socket_connector = std::make_unique<CConnectorSocket>(port, ip_address);
}

void CConnector::Connect()
{
	m_socket_connector.get()->Connect();
}

int CConnector::GetHandle() const
{
	return m_socket_connector->GetHandle();
}
