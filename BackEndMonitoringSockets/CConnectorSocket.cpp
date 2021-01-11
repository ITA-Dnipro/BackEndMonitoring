#include "CConnectorSocket.h"

namespace ConnectorSocket
{
    CConnectorSocket::CConnectorSocket(const int port, const std::string& ip_address)
        : Socket::CSocket(port, ip_address)
    {

    }

    bool CConnectorSocket::Connect()
    {
        if (connect(m_socket, (sockaddr*)&m_address, sizeof(m_address)) == SOCKET_ERROR)
        {
            return false;
        }
        return true;
    }
}



