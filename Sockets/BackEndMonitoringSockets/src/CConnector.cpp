#include "stdafx.h"
#include "CConnector.h"

CConnector::CConnector(const int port, const std::string& ip_address,
	std::shared_ptr<CLogger> logger) : m_logger(logger)
{
	m_socket_connector = InitSocketConnector(port, ip_address);
}

bool CConnector::Connect()
{
	return m_socket_connector.get()->Connect();
}

int CConnector::GetHandle() const
{
	return m_socket_connector->GetHandle();
}

std::unique_ptr<CConnectorSocket> CConnector::InitSocketConnector
	(const int port, const std::string& ip_address)
{
	return std::move(std::make_unique<CConnectorSocket>(port, ip_address, 
		m_logger));
}
