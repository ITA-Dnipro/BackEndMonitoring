#pragma once
#include "PlatformUtils.h"

class CSockAddress
{
public:
	explicit CSockAddress() = delete;
	explicit CSockAddress(const int port, const std::string& ip_address);
	CSockAddress(const CSockAddress& obj) = delete;
	CSockAddress(CSockAddress&& obj) noexcept = delete;
	CSockAddress& operator = (const CSockAddress & obj) = delete;

	sockaddress& GetSocketAddress();

private:
	void InitAddress();

	sockaddress m_socket_address;
	std::string m_ip_address;
	int m_port;
};


