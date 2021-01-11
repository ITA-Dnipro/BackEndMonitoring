#include "stdafx.h"
#pragma warning(disable: 4996)

CAcceptorSocket::CAcceptorSocket(const int port,
	const std::string& ip_address) : CSocket(port, ip_address)
{
	Open(port, ip_address);
}

int CAcceptorSocket::AcceptIncommingCalls()
{
	int sizeofaddr = sizeof(m_address);
	int new_socket = static_cast<int>(accept(m_socket,
		NULL, NULL));
	//(SOCKADDR*)&m_address, &sizeofaddr));

	return new_socket;
}

bool CAcceptorSocket::Open(const int port, const std::string& ip_address)
{
	m_address.sin_addr.s_addr = inet_addr(ip_address.c_str());
	m_address.sin_port = htons(port);
	m_address.sin_family = AF_INET;

	if (bind(m_socket, (SOCKADDR*)&m_address,
		sizeof(m_address) != SOCKET_ERROR))
	{
		std::cout << "bind socket " << m_socket << std::endl;
		//if (listen(m_socket, SOMAXCONN) != SOCKET_ERROR)
		//{
		//	std::cout << "listening" << std::endl;
		//	return true;
		//}
		while (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
		{
			std::cout << "listening" << std::endl;
			return true;
		}
	}

	std::cout << "cannot bind socket" << std::endl;

	return false;
}

