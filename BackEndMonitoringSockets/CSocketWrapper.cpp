#include "stdafx.h"
#include "CSocketWrapper.h"
#pragma warning(disable: 4996)

CSocketWrapper::CSocketWrapper(const int socket, 
	std::shared_ptr<CLogger> logger) : CSocket(socket, logger)
{ }

std::string CSocketWrapper::Receive(const int socket)
{
	size_t msg_size = ReceiveMessageLength(socket);
	std::string received_line;

	char* symb = new char[1];
	size_t counter = msg_size;
	while (true)
	{
		if (recv(socket, symb, 1, NULL) == CONNECTION_ERROR)
		{
			return "Error receiving data";
		}
		if (symb[0] == '\0')
		{
			continue;
		}

		received_line += symb[0];

		if (!--counter)
		{
			break;
		}
	}
	delete[] symb;

	if (!IsAllDataReceived(msg_size, received_line.length()))
	{
		return "Part of the data is lost";
	}

	return received_line;
}

bool CSocketWrapper::Send(const int socket, const std::string& line)
{
	if (!SendMessageLength(socket, line.length()))
	{
		return false;
	}

	if (send(socket, line.c_str(), line.length(), 0) == CONNECTION_ERROR)
	{
		return false;
	}
	return true;
}

bool CSocketWrapper::IsAllDataReceived(size_t msg_size,
	size_t received_msg_size) const
{
	return msg_size == received_msg_size;
}

bool CSocketWrapper::SendMessageLength(const int socket,  size_t length)
{
	if (send(socket, reinterpret_cast<char*>(&length),
		sizeof(length), NULL) != CONNECTION_ERROR)
	{

		return true;
	}
	return false;
}

size_t CSocketWrapper::ReceiveMessageLength(const int client_socket)
{
	size_t msg_size = 0;
	if (recv(client_socket, reinterpret_cast<char*>(&msg_size), 
		sizeof(msg_size), NULL) != CONNECTION_ERROR)
	{
		return msg_size;
	}
	return 0;
}
