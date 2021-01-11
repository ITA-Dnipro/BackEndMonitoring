#include "stdafx.h"

CConnectorSocket::CConnectorSocket(const int port,
    const std::string& ip_address) : CSocket(port, ip_address)
{

}

bool CConnectorSocket::Connect()
{
    std::cout << "connect" << std::endl;
    if (connect(m_socket, (sockaddr*)&m_address,
        sizeof(m_address)) == SOCKET_ERROR)
    {
        std::cout << "success connection" << std::endl;
        return false;
    }
    std::cout << "success connection" << std::endl;

    return true;
}



