 #pragma once

class CSocket;

//This class allows to send and receive data from one side to another
class CSocketWrapper
{
public:
	CSocketWrapper() = default;
	CSocketWrapper(const CSocketWrapper&) = delete;
	CSocketWrapper(CSocketWrapper&&) noexcept = delete;
	~CSocketWrapper() noexcept = default;
	CSocketWrapper& operator=(CSocketWrapper&&) = delete;
	CSocketWrapper& operator=(const CSocketWrapper&) = delete;

	bool Receive(const CSocket& client_socket, std::string& message);
	bool Send(const CSocket& client_socket, const std::string& line);
	bool SendHeaderSize(const CSocket& client_socket, size_t header_size);
	bool CanReceiveData(const CSocket& socket) const;
	bool IsErrorOccurred(const CSocket& socket) const;

private:
	[[nodiscard]] int ReceiveHeader(const CSocket& client_socket) const;
	bool ReceiveHeaderKey(const CSocket& client_socket,
		const std::string& key) const;
	bool IsAllDataReceived(int msg_size, int received_msg_size) const;
	[[nodiscard]] int ConvertDataToInt(const std::string& data) const;
};