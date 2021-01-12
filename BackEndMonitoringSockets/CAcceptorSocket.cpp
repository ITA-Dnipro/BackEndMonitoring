#include "stdafx.h"
#include "CAcceptorSocket.h"
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

CAcceptorSocket::CAcceptorSocket(const int port,
	const std::string& ip_address) : CSocket(port, ip_address)
{
	Open(port, ip_address);
}

int CAcceptorSocket::AcceptIncommingCalls()
{
	return static_cast<int>(accept(m_socket, NULL, NULL));
}

bool CAcceptorSocket::Open(const int port, const std::string& ip_address)
{

	if (::bind(m_socket, (SOCKADDR*)&m_address, sizeof(m_address)) != 0)
	{
		return false;
	}
	if (::listen(m_socket, SOMAXCONN) == 0)
	{
		return true;
	}

	return false;
}

