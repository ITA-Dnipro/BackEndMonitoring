#include "stdafx.h"
#include "CConnectorSocket.h"

CConnectorSocket::CConnectorSocket(const int port,
    const std::string& ip_address, std::shared_ptr<CLogger> logger) 
    : CSocket(port, ip_address, logger)
{ 
    bool isReuse = true;
    int k = setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&isReuse, sizeof(isReuse));
}

bool CConnectorSocket::Connect()
{
    if (connect(m_socket, (sockaddr*)&m_address, sizeof(m_address)) == SOCKET_ERROR)
    {
        std::cout << "Fail connection to the server" << std::endl;
        return false;
    }
    std::cout << "Success connection to the server" << std::endl;

    return true;
}



