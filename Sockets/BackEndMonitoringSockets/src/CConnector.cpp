#include "stdafx.h"

#include "CConnector.h"

CConnector::CConnector(const int port, const std::string& ip_address)
	: m_socket_connector(port, ip_address)
{
}

CConnector::~CConnector() noexcept
{
	PlatformUtils::CloseSocket(m_socket_connector.GetSocketFD());
}

bool CConnector::Initialize()
{
	return m_socket_connector.InitSocket();
}

bool CConnector::Connect() const
{
	if(!m_socket_connector.IsValidSocket())
	{
		return false;
	}
	
	sockaddress current_address = m_socket_connector.GetSocketAddress();

	if (PlatformUtils::Connect(m_socket_connector.GetSocketFD(), 
		current_address))
    {
		return true;
    }
	return false;
}

CSocket& CConnector::GetSocket()
{
	return m_socket_connector;
}

