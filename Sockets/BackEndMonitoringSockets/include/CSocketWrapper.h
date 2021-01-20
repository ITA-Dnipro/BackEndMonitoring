 #pragma once

//This class allows to send and receive data from one side to another
class CSocketWrapper
{
public:
	CSocketWrapper();

	std::string Receive(const int client_socket);
	bool Send(const int client_socket, const std::string& line);

private:
	const int CONNECTION_ERROR = -1;

	bool IsAllDataReceived(int msg_size, int received_msg_size) const;
	bool SendMessageLength(const int client_socket, int length);
	int ReceiveMessageLength(const int client_socket);
};