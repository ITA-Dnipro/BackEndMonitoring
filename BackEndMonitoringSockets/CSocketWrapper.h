 #pragma once
#include "stdafx.h"
#include "CSocket.h"

//This class allows to send and receive data from one side to another
class CSocketWrapper : public CSocket
{
public:
	CSocketWrapper() = delete;
	CSocketWrapper(const int socket, std::shared_ptr<CLogger> logger);
	std::string Receive(const int client_socket);
	bool Send(const int client_socket, const std::string& line);

private:
	const int CONNECTION_ERROR = -1;

	bool IsAllDataReceived(size_t msg_size, size_t received_msg_size) const;
	bool SendMessageLength(const int client_socket, size_t length);
	size_t ReceiveMessageLength(const int client_socket);
};