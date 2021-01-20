#include "stdafx.h"
#include "CSocket.h"

CSocket::CSocket(const int port, const std::string& ip_address)
{
	SetSocketAddress(port, ip_address);
	m_socket = InitSocket();
}

CSocket::~CSocket()
{
	if (CloseSocket()) {
		// log pos
	}
	else
	{
		// LOG + WSAGetLastError()
	}
}

int CSocket::GetHandle() const
{
	return static_cast<int>(m_socket);
}

int CSocket::InitSocket()
{
	int new_socket = static_cast<int>(socket(AF_INET, SOCK_STREAM, NULL));
	if (!IsValidSocket())
	{
		// LOGGER + WSAGetLastError()
	}

	return new_socket;
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
	if (m_socket == INVALID_SOCKET)
	{
		return false;
	}
	return true;
}

bool CSocket::CloseSocket()
{
	if (m_socket != INVALID_SOCKET)
	{
		if (closesocket(m_socket) != INVALID_SOCKET)
		{
			return true;
		}
	}
	return false;
}

sockaddr_in CSocket::GetSocketAddress() const
{
	return m_address;
}
