#include "stdafx.h"
#include "CSocket.h"
#pragma warning(disable: 4996)

CSocket::CSocket(const int port, const std::string& ip_address, 
	std::shared_ptr<CLogger> logger) : CBaseSocket(logger)
{
	SetSocketAddress(port, ip_address);
	m_socket = InitSocket();
}

CSocket::CSocket(const int socket, std::shared_ptr<CLogger> logger)
	: CBaseSocket(logger)
{
	m_socket = socket;
	m_address = { 0 };
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

int CSocket::InitSocket()
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