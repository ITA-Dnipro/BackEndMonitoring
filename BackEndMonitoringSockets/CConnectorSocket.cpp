#include "CConnectorSocket.h"

namespace ConnectorSocket
{
    CConnectorSocket::CConnectorSocket(const int port, 
        const std::string& ip_address)
        : Socket::CSocket(port, ip_address)
    {

    }

    bool CConnectorSocket::Connect()
    {
        std::cout << "connect";
        if (connect(m_socket, (sockaddr*)&m_address, 
            sizeof(m_address)) == SOCKET_ERROR)
        {
            std::cout << "success connection";
            return false;
        }
        std::cout << "success connection";

        return true;
    }
}



