#include "stdafx.h"
#include "CSocketWrapper.h"
#pragma warning(disable: 4996)

CSocketWrapper::CSocketWrapper(const int socket)
{
	m_socket = socket;
}

CSocketWrapper::~CSocketWrapper()
{
	closesocket(m_socket);
}

int CSocketWrapper::GetHandle() const
{
	return static_cast<int>(m_socket);
}

std::string CSocketWrapper::Receive(const int client_socket)
{
	unsigned msg_size;
	std::string received_line;

	recv(client_socket, reinterpret_cast<char*>(&msg_size), sizeof(msg_size), NULL);
	//char* msg_c_str = new char[msg_size + 1];
	//msg_c_str[msg_size] = '\0';
	char* symb = new char[1];
	while (true)
	{
		auto res = recv(client_socket, symb, 1, NULL);
		if (res == -1)
		{
			return "Error reciving data";
		}
		if (symb[0] == '\0')
		{
			continue;
		}

		received_line += symb[0];

		if (!--msg_size)
		{
			break;
		}
	}

	//received_line = msg_c_str;
	//delete[] msg_c_str;
	return received_line;
	//std::string received_line;
	//char buff[1024];
	//recv(client_socket, buff, 1024, 0);
	//return buff;


	//while (true)
	//{
	//	char symb;

	//	switch (recv(client_socket, &symb, 1, 0))
	//	{
	//	case 0:
	//		return received_line;
	//	case -1:
	//		return "";
	//	}

	//	std::cout << symb;
	//	received_line += symb;

	//	if (symb == '\n')
	//	{
	//		return received_line;
	//	}
	//}
}

bool CSocketWrapper::Send(const int client_socket, const std::string& line)
{
	//std::cout << line;
	size_t msg_size = line.length();
	auto res = send(client_socket, reinterpret_cast<char*>(&msg_size), sizeof(msg_size), NULL);
	if (send(client_socket, line.c_str(), line.length(), 0)
		== INVALID_SOCKET)
	{
		return false;
	}
	return true;
}
