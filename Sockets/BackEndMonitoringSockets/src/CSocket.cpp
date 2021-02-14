#include "stdafx.h"

#include "CSocket.h"

CSocket::CSocket(const int port, const std::string& ip_address)
	: CBaseSocket(c_invalid_socket)
{
	InitAddress(port, ip_address);
}

CSocket::CSocket(const int port, const std::string& ip_address, int socket_fd)
	: CBaseSocket(socket_fd)
{
	InitAddress(port, ip_address);
}

CSocket::CSocket(sockaddress address, int socket_fd)
	: CBaseSocket(socket_fd), m_address(address)
{ }

void CSocket::InitAddress(const int port,
                          const std::string& ip_address)
{
	m_address.sin_family = AF_INET;
	m_address.sin_port = htons(port);
	inet_pton(AF_INET, ip_address.c_str(), &(m_address.sin_addr.s_addr));
}

bool CSocket::IsValidSocket() const
{
	if (m_socket == c_invalid_socket || m_socket == c_error_socket)
	{
		return false;
	}
	return true;
}

sockaddr_in CSocket::GetSocketAddress() const
{
	return m_address;
}

