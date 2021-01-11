#include "stdafx.h"
#include "CAcceptorSocket.h"
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

	return new_socket;
}

bool CAcceptorSocket::Open(const int port, const std::string& ip_address)
{
	
	if (bind(m_socket, (SOCKADDR*)&m_address, sizeof(m_address) 
		!= 0))
	{
		std::cout << "bind socket " << m_socket << std::endl;
		//if (listen(m_socket, SOMAXCONN) != SOCKET_ERROR)
		//{
		//	std::cout << "listening" << std::endl;
		//	return true;
		//}
		while(true)
		{
			std::cout << m_socket << std::endl;
			if (listen(m_socket, SOMAXCONN) != 0)
			{
				std::cout << "listening" << std::endl;
				return true;
			}
			std::cout << "try listen " << WSAGetLastError() << std::endl;
		}
	}

	std::cout << "cannot bind socket" << std::endl;

	return false;
}

