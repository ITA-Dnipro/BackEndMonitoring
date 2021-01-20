#include "stdafx.h"
#include "CConnector.h"

CConnector::CConnector(const int port, const std::string& ip_address)
{
	m_socket_connector = InitSocketConnector(port, ip_address);
}

bool CConnector::Connect()
{
	sockaddr_in current_address = m_socket_connector->GetSocketAddress();

	if (connect(m_socket_connector->GetHandle(), (sockaddr*)&current_address,
		sizeof(current_address)) == SOCKET_ERROR)
    {
        std::cout << "Fail connection to the server" << std::endl;
        return false;
    }
    std::cout << "Success connection to the server" << std::endl;

    return true;
}

int CConnector::GetHandle() const
{
	return m_socket_connector->GetHandle();
}

std::unique_ptr<CSocket> CConnector::InitSocketConnector
	(const int port, const std::string& ip_address)
{
	return std::move(std::make_unique<CSocket>(port, ip_address));
}
