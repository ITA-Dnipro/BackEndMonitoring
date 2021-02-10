 #pragma once

//This class allows to send and receive data from one side to another
class CSocketWrapper
{
public:
	CSocketWrapper() = default;
	CSocketWrapper(const CSocketWrapper&) = delete;
	CSocketWrapper(CSocketWrapper&&) noexcept = delete;
	~CSocketWrapper() noexcept = default;

	bool Receive(const int client_socket, std::string& message);
	bool Send(const int client_socket, const std::string& line);
	bool CanReceiveData(const int socket) const;
	bool IsErrorOccured(const int socket) const;

private:
	static const int c_max_buffer_size = 500u;
	const int c_connection_error = -1;

	[[nodiscard]] std::string CreateHeader(const int size);
	[[nodiscard]] int GetSizeFromHeader(const int socket) const;
	bool IsAllDataReceived(int msg_size, int received_msg_size) const;
	[[nodiscard]] int ConvertDataToInt(const std::string& data) const;
};