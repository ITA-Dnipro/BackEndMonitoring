#include "stdafx.h"
#include "CSocket.h"
#pragma warning(disable: 4996)

CSocket::CSocket(const int port, const std::string& ip_address)
	: m_port(port)
{
	SetSocketAddress(port, ip_address);
	m_socket = InitSocket(port, ip_address);
}

CSocket::~CSocket()
{
	if (CloseSocket()) {
		// log pos
	}
	else
	{
		// LOG WSAGetLastError()
	}
}

int CSocket::GetHandle() const
{
	return static_cast<int>(m_socket);
}

int CSocket::InitSocket(const int port, const std::string& ip_address)
{
	SOCKET new_socket = socket(AF_INET, SOCK_STREAM, NULL);
	if (!IsValidSocket())
	{
		// LOGGER + EXCEPTIOn
	}

	return static_cast<int>(new_socket);
}

void CSocket::SetSocketAddress(const int port,
	const std::string& ip_address)
{
	m_address.sin_family = AF_INET;
	m_address.sin_port = htons(port);
	m_address.sin_addr.s_addr = inet_addr(ip_address.c_str());
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
