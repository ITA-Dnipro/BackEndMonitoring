#include "stdafx.h"
#include "CSocket.h"

CSocket::CSocket(const int port, const std::string& ip_address)
{
	SetSocketAddress(port, ip_address);
}

int CSocket::GetHandle() const
{
	return static_cast<int>(m_socket);
}

void CSocket::SetSocketAddress(const int port,
	const std::string& ip_address)
{
	m_address.sin_family = AF_INET;
	m_address.sin_port = htons(port);
	inet_pton(AF_INET, ip_address.c_str(), &(m_address.sin_addr.s_addr));
}

bool CSocket::IsValidSocket() const
{
	if (m_socket == SOCKET_INVALID)
	{
		return false;
	}
	return true;
}

bool CSocket::CloseSocket()
{
	return PlatformUtils::CloseSocket(static_cast<int>(m_socket));
}

sockaddr_in CSocket::GetSocketAddress() const
{
	return m_address;
}
