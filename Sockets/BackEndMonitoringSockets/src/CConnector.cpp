#include "stdafx.h"
#include "CConnector.h"

CConnector::CConnector(const int port, const std::string& ip_address)
{
	m_p_socket_connector = InitSocketConnector(port, ip_address);
}

bool CConnector::Connect()
{
	sockaddress current_address = m_p_socket_connector->GetSocketAddress();

	if (PlatformUtils::Connect(m_p_socket_connector->GetSocketFD(), 
		current_address))
    {
		return true;
    }
	return false;
}

int CConnector::GetSocketFD() const
{
	return m_p_socket_connector->GetSocketFD();
}

std::unique_ptr<CSocket> CConnector::InitSocketConnector
	(const int port, const std::string& ip_address)
{
	return std::move(std::make_unique<CSocket>(port, ip_address));
}
