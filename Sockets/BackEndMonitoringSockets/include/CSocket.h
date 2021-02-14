#pragma once
#include "PlatformUtils.h"

class CSocket : public CBaseSocket
{
public:
	CSocket() = default;
	explicit CSocket(const int port, const std::string& ip_address);
	explicit CSocket(const int port, const std::string& ip_address, int socket_fd);
	explicit CSocket(sockaddress address, int socket_fd);
	CSocket(const CSocket& obj) = default;
	CSocket(CSocket&& obj) noexcept = default;
	CSocket& operator = (const CSocket& obj) = default;

	[[nodiscard]]  sockaddress GetSocketAddress() const;
	void InitAddress(const int port, const std::string& ip_address);
	bool IsValidSocket() const;

private:
	sockaddress m_address;

};
