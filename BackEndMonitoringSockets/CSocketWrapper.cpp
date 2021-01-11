#include "stdafx.h"
#include "CSocketWrapper.h"
#pragma warning(disable: 4996)

CSocketWrapper::CSocketWrapper()
{
	m_socket = INVALID_SOCKET;
}

CSocketWrapper::CSocketWrapper(const int socket)
{
	m_socket = socket;
}

CSocketWrapper::~CSocketWrapper()
{
	closesocket(m_socket);
}

void CSocketWrapper::SetSocket(const int socket)
{
	std::cout << socket << " - socket in wrapper" << std::endl;
	m_socket = socket;
}

int CSocketWrapper::GetHandle() const
{
	return static_cast<int>(m_socket);
}

std::string CSocketWrapper::Receive(const int client_socket)
{
	std::string received_line;
	while (true)
	{
		char symb;

		switch (recv(client_socket, &symb, 1, 0))
		{
		case 0:
			return received_line;
		case -1:
			return "";
		}

		std::cout << symb;
		received_line += symb;

		if (symb == '\n')
		{
			return received_line;
		}
	}
}

bool CSocketWrapper::Send(const int client_socket, const std::string& line)
{
	std::cout << line;
	if (send(client_socket, line.c_str(), line.length(), 0)
		== INVALID_SOCKET)
	{
		return false;
	}
	return true;
}
