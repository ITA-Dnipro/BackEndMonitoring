 #pragma once

//This class allows to send and receive data from one side to another
class CSocketWrapper
{
public:
	CSocketWrapper();

	std::string Receive(const int client_socket);
	bool Send(const int client_socket, const std::string& line);
	bool CanReceiveData(const int socket) const;

private:
	const size_t MAX_BUFFER_SIZE = 2000u;
	const int CONNECTION_ERROR = -1;

	std::string CreateHeader(const int size);
	int GetSizeFromHeader(const int socket) const;
	bool IsAllDataReceived(int msg_size, int received_msg_size) const;
	int ConvertDataToInt(const std::string& data) const;
};