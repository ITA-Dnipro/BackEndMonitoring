#include "stdafx.h"
#include "CConnectorSocket.h"

CConnectorSocket::CConnectorSocket(const int port,
    const std::string& ip_address, std::shared_ptr<CLogger> logger) 
    : CSocket(port, ip_address, logger)
{
}

bool CConnectorSocket::Connect()
{
    if (connect(m_socket, (sockaddr*)&m_address, sizeof(m_address)) == SOCKET_ERROR)
    {
        std::cout << "fail connection" << std::endl;
        return false;
    }
    std::cout << "success connection" << std::endl;

    return true;
}



